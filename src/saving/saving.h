// saving/saving.h
#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  EVENT_DRIVEN,
  REAL_TIME,
  LOGIC_SIM,
  DRIVER_COUNT
} DriverID;

typedef struct {
  char name[16];
  char version[16];
  bool fullscreen;
  DriverID driver;
} AppSettings;

bool save_settings(AppSettings *settings);
bool load_settings(AppSettings *settings);
