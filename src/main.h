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
  char name[256];
  const char* version;
  bool fullscreen;
  DriverID driver;
} AppSettings;

typedef struct { 
  SDL_Window* window;
  SDL_Renderer* renderer;

  AppSettings settings;
} AppContext;
