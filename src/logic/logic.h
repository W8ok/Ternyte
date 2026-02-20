// logic/logic.h
#pragma once

#include <stdint.h>

#define MAX_GATE_INPUTS 2

typedef enum {
  BINARY_NOT,
  BINARY_AND,
  BINARY_OR,
  BINARY_XOR,
  BINARY_TYPE_COUNT
} GateType;

typedef enum {
  RIGHT,
  DOWN,
  LEFT,
  UP,
} Rotation;

typedef struct {
  Rotation rotation;
  GateType type;
  int x, y;
  int output_idx;
  int input_idx[MAX_GATE_INPUTS];
} Gates;

typedef struct {
  int x1, y1, x2, y2;
  int connection_idx;
} Wires;

typedef struct {
  Gates* gate;
  Wires* wire;
  uint8_t gate_count;
  uint8_t wire_count;
  bool wire_started;
  int wire_capacity;
  int gate_capacity;
} LogicContext;
