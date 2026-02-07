// main.h
#pragma once

#include <SDL3/SDL.h>
#include <stdio.h>

typedef enum {
  EVENT_DRIVEN,
  REAL_TIME,
  DRIVER_COUNT
} DriverID;

typedef struct { 
  SDL_Window* window;
  SDL_Renderer* renderer;
  const char* version;
  const char* name;

  DriverID driver;
} AppContext;
