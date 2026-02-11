// main.h
#pragma once

#include <stdio.h>
#include <time.h>

#include "saving/saving.h"
#include "rendering/rendering.h"
#include "logic/logic.h"

typedef struct { 
  SDL_Window* window;
  SDL_Renderer* renderer;

  RenderContext* rc;
  LogicContext* lc;

  AppSettings settings;
} AppContext;
