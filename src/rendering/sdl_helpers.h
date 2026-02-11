// rendering/sdl_helpers.h
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL3/SDL.h>

extern SDL_Renderer* sdl_renderer;

bool _render_panic(const char* msg);
bool _clear_background(SDL_Color color);
bool _set_color(SDL_Color color);
bool _render_line(SDL_FPoint start, SDL_FPoint end);

