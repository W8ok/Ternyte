// render/gate.c
#include "render.h"

void gate_render(RenderContext* rc)
{
  LogicContext* lc = (LogicContext *)rc->lc;
  uint8_t size = 20;
  
  _set_color(RED);

  for (int i = 0; i < lc->gate_count; i++)
  {
    SDL_FPoint screen_point = _grid_to_screen(
      (SDL_FPoint) {
        lc->gate[i].x,
        lc->gate[i].y
      },
      rc->grid_size
    );
    SDL_FRect gate_rect = {
      screen_point.x,
      screen_point.y,
      size,
      size
    };

    _render_fill_rect(&gate_rect);
  }
}

bool update_gate_capacity(LogicContext* lc, int needed)
{
  int required = lc->gate_count + needed;
  if (required <= lc->gate_capacity)
    return true;
  
  // Round up to nearest 100
  int new_capacity = ((required + 99) / 100) * 100;
  
  Gates* new_gate = SDL_realloc(lc->gate, new_capacity * sizeof(Gates));
  if (!new_gate)
  {
    printf("Failed to allocate memory for new gate\n");
    return false;
  }
  
  lc->gate = new_gate;
  lc->gate_capacity = new_capacity;
  return true;
}

bool gate_creation(RenderContext* rc, SDL_FPoint point)
{
  LogicContext* lc = (LogicContext *)rc->lc;

  if (lc->gate_count >= lc->gate_capacity)
    if (!update_gate_capacity(lc, 1))
      return false;

  SDL_FPoint grid_point = _screen_to_grid(point, rc->grid_size);

  lc->gate[lc->gate_count].x = grid_point.x;
  lc->gate[lc->gate_count].y = grid_point.y;
  lc->gate_count++;
  return true;
}
