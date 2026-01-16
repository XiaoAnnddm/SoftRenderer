#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

namespace platform {
class Sdl_Texture {
public:
  bool create(SDL_Renderer *renderer, int width, int height);

  void destroy();

  void update(const std::vector<uint32_t> &data);

  // for ImGui use
  SDL_Texture *texture() const { return m_texture; }
  int width() const { return m_width; }
  int height() const { return m_height; }

private:
  SDL_Texture *m_texture = nullptr;
  int m_width = 0;
  int m_height = 0;
};
} // namespace platform
