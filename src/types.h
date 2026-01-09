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
  bool selected;
  bool deleted;
  Color color;
} wire;

extern wire wires[MAX_WIRES];
extern int wire_count;


// Tooling
typedef enum {
    TOOL_SELECT,
    TOOL_WIRE,
    TOOL_COMPONENT  // for later use in component selection
} Tool;

#define MAX_UNDO 256

typedef enum {
    OP_ADD_WIRE,
    OP_DELETE_WIRE,
    //OP_MOVE_WIRE
} operation_type;

typedef struct {
    operation_type type;
    int wire_index;
    wire wire_state;
} undo_entry;

extern undo_entry undo_stack[MAX_UNDO];
extern int undo_top;


// Gates
#define BIT_FALSE  ((bit)0)
#define BIT_TRUE   ((bit)1)

#define TRIT_MINUS ((trit)-1)
#define TRIT_ZERO  ((trit)0)
#define TRIT_PLUS  ((trit)1)

typedef bool bit;
typedef int8_t trit;


#endif
