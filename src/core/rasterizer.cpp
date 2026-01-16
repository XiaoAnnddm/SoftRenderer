#include "rasterizer.h"

#include <algorithm>
#include <utility>

namespace core {
void Rasterizer::Init(int width, int height) {
  w_ = width;
  h_ = height;
  frame_buf.resize(width * height);
}
void Rasterizer::clear() {
  if (!valid()) {
    return;
  }

  std::fill(frame_buf.begin(), frame_buf.end(), 0);
}

void Rasterizer::put_pixel(int x, int y, Color color) {
  frame_buf[y * w_ + x] = color;
}

void Rasterizer::draw_line(Vec3 &a, Vec3 &b, Color color) {
  bool steep = std::abs(b.y - a.y) > std::abs(b.x - a.x);
  if (steep) {
    std::swap(a.x, a.y);
    std::swap(b.x, b.y);
  }
  if (a.x > b.x) {
    std::swap(a.x, b.x);
    std::swap(a.y, b.y);
  }

  int y = a.y;
  int ierror = 0;
  for (int x = a.x; x < b.x; ++x) {
    if (steep) {
      put_pixel(y, x, color);
    } else {
      put_pixel(x, y, color);
    }

    ierror += 2 * std::abs(b.y - a.y);
    y += (b.y > a.y ? 1 : -1) * (ierror > b.x - a.x);
    ierror -= 2 * (b.x - a.x) * (ierror > b.x - a.x);
  }
}

float Rasterizer::signed_triangle_area(const Vec3 &a, const Vec3 &b,
                                       const Vec3 &c) {
  return 0.5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) +
                (a.y - c.y) * (a.x + c.x));
}

void Rasterizer::draw_filled_triangle(const Vec3 &pa, const Vec3 &pb,
                                      const Vec3 &pc, Color color) {
  if (!valid()) {
    return;
  }

  int min_x = (int)std::floor(std::min({pa.x, pb.x, pc.x}));
  int min_y = (int)std::floor(std::min({pa.y, pb.y, pc.y}));
  int max_x = (int)std::floor(std::max({pa.x, pb.x, pc.x}));
  int max_y = (int)std::floor(std::max({pa.y, pb.y, pc.y}));

  min_x = std::max(min_x, 0);
  min_y = std::max(min_y, 0);
  max_x = std::min(max_x, w_ - 1);
  max_y = std::min(max_y, h_ - 1);

  float area = signed_triangle_area(pa, pb, pc);
  for (int y = min_y; y <= max_y; ++y) {
    for (int x = min_x; x <= max_x; ++x) {
      float a = signed_triangle_area({x, y, 0}, pb, pc) / area;
      float b = signed_triangle_area({x, y, 0}, pc, pa) / area;
      float c = signed_triangle_area({x, y, 0}, pa, pb) / area;
      if (a >= 0 && b >= 0 && c >= 0) {
        put_pixel(x, y, color);
      }
    }
  }
}

} // namespace core
