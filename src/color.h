#pragma once

#include "types.h"

inline constexpr Color make_color(u8 r, u8 g, u8 b, u8 a = 255) {
  return (a << 24) | (r << 16) | (g << 8) | b;
}

namespace colors {
inline constexpr Color Black = make_color(0, 0, 0);
inline constexpr Color White = make_color(255, 255, 255);
inline constexpr Color Red = make_color(255, 0, 0);
inline constexpr Color Green = make_color(0, 255, 0);
inline constexpr Color Blue = make_color(0, 0, 255);
inline constexpr Color Gray = make_color(128, 128, 128);
inline constexpr Color DarkGray = make_color(30, 30, 30);
} // namespace colors
