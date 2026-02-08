// main.h
#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "saving/save.h"

typedef struct { 
  SDL_Window* window;
  SDL_Renderer* renderer;

  AppSettings settings;
} AppContext;
