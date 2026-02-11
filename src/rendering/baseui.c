// rendering/baseui.c
#include "rendering.h"

void render_grid(RenderContext* rc, int cell_size)
{
  int w, h;
  SDL_GetWindowSize(rc->window, &w, &h);

  _set_color(GRAY);

  for (int x = 0; x <= w; x += cell_size)
  {
    SDL_FPoint start = { x, 0 };
    SDL_FPoint end = { x, h };
    if (!_render_line(start, end))
      _render_panic("Grid vertical line failed\n");
  }

  for (int y = 0; y <= h; y += cell_size)
  {
    SDL_FPoint start = { 0, y };
    SDL_FPoint end = { w, y };
    if (!_render_line(start, end))
      _render_panic("Grid horizontal line failed\n");
  }
}

void render_main(RenderContext* rc)
{
  if (!_clear_background(DARK_GRAY))
    return;

  render_grid(rc, 20);
}
