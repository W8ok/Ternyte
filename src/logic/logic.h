// logic/logic.h
#pragma once

#include <stdint.h>

typedef struct {
  int x, y;
  uint8_t size;
} Gates;

typedef struct {
  Gates* gate;
  size_t gate_count;
} LogicContext;
