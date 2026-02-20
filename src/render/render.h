// render/render.h
#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>

#include "colors.h"
#include "sdl_helpers.h"
#include "coords.h"
#include "../logic/logic.h"

typedef struct {
  float zoom;
  SDL_FPoint offset;
} Camera; // Eventually :3

typedef struct {
  SDL_Window* window;
  SDL_Renderer* sdl_renderer; 

  Camera cam;

  LogicContext* lc;

  uint8_t grid_size;
} RenderContext;

void render_main(RenderContext* rc);
void wire_render(RenderContext* rc);
bool wire_creation(RenderContext* rc, SDL_FPoint point);

void gate_render(RenderContext* rc);
bool gate_creation(RenderContext* rc, SDL_FPoint point);
