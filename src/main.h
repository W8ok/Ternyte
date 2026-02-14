// main.h
#pragma once

#include <stdio.h>
#include <time.h>

#include "save/save.h"
#include "render/render.h"
#include "gui/gui.h"
#include "logic/logic.h"

typedef struct { 
  SDL_Window* window;
  SDL_Renderer* renderer;

  RenderContext* rc;
  UiContext* uc;
  LogicContext* lc;

  AppSettings settings;
} AppContext;
