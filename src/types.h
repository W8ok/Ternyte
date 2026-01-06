// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

// UI elements
#define SCREEN_SIZE_FACTOR 0.8
#define FPS 60
#define GRID_SIZE 20 // Pixels between the gridlines
#define SEPARATOR_THICKNESS 3 // Pixels thick

typedef struct{
  Rectangle selectionPanel;
  Rectangle workspace;
  int screenWidth;
  int screenHeight;
  int screenCenterX;
  int screenCenterY;
  int currentMonitor;
} ui_state;

// Wires
#define WIRE_THICKNESS 3
#define MAX_WIRES 65536

typedef struct{
  Vector2 start;
  Vector2 end;
} wire;

extern wire wires[MAX_WIRES];
extern int wire_count;

// Gates
#define BIT_FALSE  ((bit)0)
#define BIT_TRUE   ((bit)1)

#define TRIT_MINUS ((trit)-1)
#define TRIT_ZERO  ((trit)0)
#define TRIT_PLUS  ((trit)1)

typedef bool bit;
typedef int8_t trit;


#endif
