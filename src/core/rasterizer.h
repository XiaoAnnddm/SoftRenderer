#pragma once

#include "types.h"

namespace core {
class Rasterizer {
public:
  void Init(int width, int height);

  void clear();

  void put_pixel(int x, int y, Color color);
  void draw_line(Vec3 &a, Vec3 &b, Color color);
  void draw_filled_triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c,
                            Color color);
  float signed_triangle_area(const Vec3 &a, const Vec3 &b, const Vec3 &c);

  std::vector<Color> &frame_buffer() { return frame_buf; }

private:
  std::vector<Color> frame_buf;
  int w_ = 0;
  int h_ = 0;

  bool valid() const { return w_ > 0 && h_ > 0; }
};

} // namespace core
