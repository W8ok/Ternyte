// render/wire.c
#include "render.h"

void wire_render(RenderContext* rc)
{
  LogicContext* lc = (LogicContext *)rc->lc;
  
  _set_color(GRAY);
  SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3");

  for (int i = 0; i < lc->wire_count; i++)
  {
    SDL_FPoint start = { lc->wire[i].x1, lc->wire[i].y1 };
    SDL_FPoint end = { lc->wire[i].x2, lc->wire[i].y2 };
    _render_line(start, end);
  }
}

void wire_preview(RenderContext* rc)
{
  //connect up to mouse input :3:w

  static bool wire_started = false;
}
