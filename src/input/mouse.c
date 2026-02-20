// input/mouse.c
#include "input.h"

void mouse_main(AppContext* app, SDL_MouseButtonEvent button)
{
  if (button.button == SDL_BUTTON_LEFT)
  {
    SDL_FPoint point = { button.x, button.y };
    wire_creation(app->rc, point);
  }
  else if (button.button == SDL_BUTTON_RIGHT)
  {
    SDL_FPoint point = { button.x, button.y };
    gate_creation(app->rc, point);
  }
}
