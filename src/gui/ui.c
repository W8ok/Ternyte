// gui/ui.c
#define CLAY_IMPLEMENTATION
#include "gui.h"

void ui_grid(UiContext* uc, int cell_size)
{
  // Could just make this a texture and save lots of processing
  int w, h;
  SDL_GetWindowSize(uc->rc->window, &w, &h);

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

void ui_main(UiContext* uc)
{
  if (!_clear_background(DARK_GRAY))
    return;

  ui_grid(uc, uc->rc->grid_size);
}
