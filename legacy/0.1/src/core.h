// core/core.h
#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

// Constants
#define WIRE_THICKNESS 3
#define MAX_WIRES 65536
#define MAX_UNDO 256
#define MAX_GATES 65536

#define SCREEN_SIZE_FACTOR 0.8
#define FPS 60
#define GRID_SIZE 20
#define SEPARATOR_THICKNESS 3

#define BIT_FALSE  ((bit)0)
#define BIT_TRUE   ((bit)1)
#define TRIT_MINUS ((trit)-1)
#define TRIT_ZERO  ((trit)0)
#define TRIT_PLUS  ((trit)1)

// Enums
typedef enum {
  TOOL_SELECT,
  TOOL_WIRE,
  TOOL_COMPONENT
} Tool;

typedef enum {
  AND,
  OR,
  NOT,
  XOR,
  INPUT
} BinaryGateType;

typedef enum {
  OP_ADD_WIRE,
  OP_DELETE_WIRE,
} operation_type;

// Basic Types
typedef bool bit;
typedef int8_t trit;

// Simple Structs
typedef struct{
  Vector2 start;
  Vector2 end;
  bool selected;
  bool deleted;
  Color color;
} Wire;

typedef struct {
    operation_type type;
    int wire_index;
    Wire wire_state;
} undo_entry;

typedef struct{
  BinaryGateType gate_type;
  Vector2 position;
  Vector2 size;
  bool selected;
  bool deleted;
  Color color;
  bool input1;
  bool input2;
  bool output;
  int input1_gate_index; 
  int input2_gate_index; 
} BinaryGate;

// Complex Structs
typedef struct{
  // UI
  Rectangle selectionPanel;
  Rectangle workspace;
  int screenWidth;
  int screenHeight;
  int screenCenterX;
  int screenCenterY;
  int currentMonitor;

  // Flags
  bool is_placing_gate;

  // Extras
  BinaryGateType selected_gate; 
  Tool current_tool;
} AppState;

// Global Declarations
extern Wire wires[MAX_WIRES];
extern int wire_count;
extern undo_entry undo_stack[MAX_UNDO];
extern int undo_top;
extern BinaryGate binary_gates[MAX_GATES];
extern int gate_count;

// Function Declarations
// Utilities
Vector2 SnapToGrid(Vector2 point, Rectangle workspace, int grid_size);

// Wires
void DrawWires(AppState* ui);
void RenderWires(void);
void SelectWires(AppState* ui);
void CutWires(void);

// UI
void DrawBaseUi(AppState* ui);
int DrawGateSelection(AppState* ui, Tool* tool);  // Changed char to void
void WindowInitialization(AppState* ui);

// Gates
void DrawBinaryGates(AppState* ui);
void CreateGate(BinaryGateType type, Vector2 position);
void RenderBinaryGates(void);
const char* GateTypeToString(BinaryGateType type);

// Tools
void Undo(void);
Tool UpdateTool(Tool current_tool);

// Logic
bit gate_not(bit a);
bit gate_and(bit a, bit b);
bit gate_nand(bit a, bit b);
bit gate_or(bit a, bit b);
bit gate_nor(bit a, bit b);
bit gate_xor(bit a, bit b);
bit gate_xnor(bit a, bit b);

trit gate_neg(trit a);
trit gate_min(trit a, trit b);
trit gate_max(trit a, trit b);
trit gate_consensus(trit a, trit b);

#endif
