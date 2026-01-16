#include "sdl_texture.h"
#include "SDL_render.h"
#include <iostream>

namespace platform {
bool Sdl_Texture::create(SDL_Renderer *renderer, int width, int height) {
  m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGRA32,
                                SDL_TEXTUREACCESS_STREAMING, width, height);
  if (!m_texture) {
    std::cerr << "SDL_CreateTexture failed: " << SDL_GetError() << '\n';
    return false;
  }

  m_width = width;
  m_height = height;
  return true;
}

void Sdl_Texture::destroy() {
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
  }
  m_width = 0;
  m_height = 0;
}

void Sdl_Texture::update(const std::vector<Color> &data) {
  if (!m_texture) {
    return;
  }

  int pitch = m_width * sizeof(uint32_t);
  SDL_UpdateTexture(m_texture, nullptr, data.data(), pitch);
}
} // namespace platform
