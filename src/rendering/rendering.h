// rendering/rendering.h
#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>

#include "colors.h"
#include "sdl_helpers.h"
#include "../logic/logic.h"

typedef struct {
  SDL_Window* window;
  SDL_Renderer* sdl_renderer; 

  const LogicContext* lc;
} RenderContext;

// baseui.c
void render_main(RenderContext* rc);
