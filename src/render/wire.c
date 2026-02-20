// render/wire.c
#include "render.h"

void wire_render(RenderContext* rc)
{
  LogicContext* lc = (LogicContext *)rc->lc;
  
  _set_color(GREEN);

  for (int i = 0; i < lc->wire_count; i++)
  {
    // Perhaps split wire into a render and logic context... to avoid this mess
    SDL_FPoint start = _grid_to_screen(
      (SDL_FPoint){
        lc->wire[i].x1,
        lc->wire[i].y1
      },
      rc->grid_size
    );

    SDL_FPoint end = _grid_to_screen(
      (SDL_FPoint){
        lc->wire[i].x2,
        lc->wire[i].y2
      },
      rc->grid_size
    );

    _render_line(start, end);
  }
}

bool update_wire_capacity(LogicContext* lc, int needed)
{
  int required = lc->wire_count + needed;
  if (required <= lc->wire_capacity)
    return true;
  
  // Round up to nearest 100
  int new_capacity = ((required + 99) / 100) * 100;
  
  Wires* new_wire = SDL_realloc(lc->wire, new_capacity * sizeof(Wires));
  if (!new_wire)
  {
    printf("Failed to allocate memory for new wire\n");
    return false;
  }
  
  lc->wire = new_wire;
  lc->wire_capacity = new_capacity;
  return true;
}

bool wire_creation(RenderContext* rc, SDL_FPoint point)
{
  LogicContext* lc = (LogicContext *)rc->lc;

  if (lc->wire_count >= lc->wire_capacity)
    if (!update_wire_capacity(lc, 1))
      return false;

  int wire_count = lc->wire_count;
  SDL_FPoint grid_point = _screen_to_grid(point, rc->grid_size);

  if (!lc->wire_started)
  {
    lc->wire[wire_count].x1 = grid_point.x;
    lc->wire[wire_count].y1 = grid_point.y;

    lc->wire_started = true;
  }
  else
  {
    lc->wire[wire_count].x2 = grid_point.x;
    lc->wire[wire_count].y2 = grid_point.y;

    lc->wire_count++;
    
    if (lc->wire_count >= lc->wire_capacity)
      if (!update_wire_capacity(lc, 1))
        return false;
    
    lc->wire[lc->wire_count].x1 = grid_point.x;
    lc->wire[lc->wire_count].y1 = grid_point.y;
  }
  return true;
}
