#pragma once
#include <SDL2/SDL.h>

namespace ui {
struct UiState {
  bool show_demo = true;
};

bool init(SDL_Window *window, SDL_Renderer *renderer);
void shutdown();

void begin_frame();
void draw(UiState &state);
void end_frame(SDL_Renderer *renderer);

void process_event(const SDL_Event &e);
} // namespace ui
