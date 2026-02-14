// render/sdl_helpers.c
#include "sdl_helpers.h"

SDL_Renderer* sdl_renderer;

bool _render_panic(const char* msg)
{
  time_t t = time(NULL);
  struct tm* tm_info = localtime(&t);

  char time_buf[20];
  strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);

  printf("[%s] Rendering: %s\n", time_buf, msg);
  return false;
}

bool _clear_background(SDL_Color color)
{
  if (!SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a))
    return _render_panic("_clear_background, color failed");

  if (!SDL_RenderClear(sdl_renderer))
    return _render_panic("_clear_background, clear failed");

  return true;
}

bool _set_color(SDL_Color color)
{
  if (!SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a))
    return _render_panic("_set_color failed");
  return true;
}

bool _render_line(SDL_FPoint start, SDL_FPoint end)
{
  if (!SDL_RenderLine(sdl_renderer, start.x, start.y, end.x, end.y))
    return _render_panic("_render_line_failed");
  return true;
}
