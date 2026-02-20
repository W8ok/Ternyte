// save/save.h
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../logic/logic.h"

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

typedef struct {
  Gates* gate;
  Wires* wire;
  uint8_t gate_count;
  uint8_t wire_count;
} CircuitContext;

bool save_settings(AppSettings *settings);
bool load_settings(AppSettings *settings);

bool make_circuit_snapshot(const LogicContext* lc, CircuitContext* cir);
bool save_circuit(CircuitContext* cir, AppSettings* settings);
bool load_circuit(LogicContext* lc, AppSettings* settings);
