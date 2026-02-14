// logic/logic.h
#pragma once

#include <stdint.h>

typedef struct {
  int x, y;
  uint8_t size;
} Gates;

typedef struct {
  int x1, y1, x2, y2;
} Wires;

typedef struct {
  Gates* gate;
  Wires* wire;
  uint8_t gate_count;
  uint8_t wire_count;
} LogicContext;
