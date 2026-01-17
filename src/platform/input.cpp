#include "input.h"

namespace platform {
void Input::begin_frame() {
  m_mouse_dx = 0;
  m_mouse_dy = 0;
}

void Input::process_event(const SDL_Event &e) {
  switch (e.type) {
  case SDL_KEYDOWN:
    m_keys_down.insert(e.key.keysym.scancode);
    break;

  case SDL_KEYUP:
    m_keys_down.erase(e.key.keysym.scancode);
    break;

  case SDL_MOUSEMOTION:
    m_mouse_dx += e.motion.xrel;
    m_mouse_dy += e.motion.yrel;
    m_mouse_x = e.motion.x;
    m_mouse_y = e.motion.y;
    break;

  case SDL_MOUSEBUTTONDOWN:
    m_mouse_buttons |= SDL_BUTTON(e.button.button);
    break;

  case SDL_MOUSEBUTTONUP:
    m_mouse_buttons &= ~SDL_BUTTON(e.button.button);
    break;

  default:
    break;
  }
}

bool Input::is_key_down(SDL_Scancode key) const {
  return m_keys_down.count(key) > 0;
}

bool Input::is_mouse_button_down(int button) const {
  return (m_mouse_buttons & SDL_BUTTON(button)) != 0;
}
} // namespace platform
