// render/coords.h
#pragma once

static inline SDL_FPoint _screen_to_grid(SDL_FPoint screen_point, float grid_size)
{
  return (SDL_FPoint)
  {
  (int)(screen_point.x / grid_size),
  (int)(screen_point.y / grid_size)
  };
}

static inline SDL_FPoint _grid_to_screen(SDL_FPoint grid_point, float grid_size)
{
  return (SDL_FPoint)
  {
  grid_point.x * grid_size,
  grid_point.y * grid_size
  };
}
