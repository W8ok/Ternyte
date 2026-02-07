// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

#include "defines.h"


typedef enum {
  Menu,
  StartSim,
  Input,
  AND,
  OR,
  XOR,
  NOT
} BaseSelectionMenuButton;

typedef enum {
  Back,
  Quit
} BaseMenuMenuButton;

typedef enum {
  BaseMenu,
  MenuMenu
} MenuState;

typedef enum {
  OperateTool,
  SelectTool,
  WireTool,
  GateTool,
  MoveTool
} Tool;

typedef enum {
  GateInput,
  GateAND,
  GateOR,
  GateXOR,
  GateNOT
} BinaryGateType;


typedef struct {
  MenuState current_menu;
  Tool current_tool;
  BinaryGateType current_binary_type;
  bool should_quit;
  bool simulate;
  bool simulation_started;
} App;

typedef struct {
  int monitor;
  Rectangle screen_rec;
  Rectangle workspace_rec;
  Rectangle selection_rec;
  Rectangle button_rec;
  Color button_color;
  Vector2 mouse_pos;
} Ui;

typedef struct {
  Color wire_color;
  Color gate_color;
  Vector2 snapped_pos;
  int wire_count;
  int gate_count;
  int max_wires;
  int max_gates;
  int next_connection_index;
  bool got_indexed;
  bool wire_started;
  bool gate_started;
  bool is_placing_gate;
} Circuit;

typedef struct {
    bool moving;
    Vector2 mouse_start_pos;
    Vector2* gate_start_pos;
    int* selected_indices;
    int selection_count;
} Move;

typedef struct {
  Vector2* contact_points; // Keeps track of everything connected together
  int contact_count;
} Sim;


typedef struct {
  Vector2 start;
  Vector2 end;
  Color color;
  int connection_index;
  bool state;
  bool deleted;
  bool selected; // Could make a selected array in Circuit, would speed up pocessing at the cost of memory usage
} Wire;

typedef struct {
  Rectangle gate_rec;
  Color color;
  BinaryGateType type;
  Vector2 input_points[MAX_GATE_INPUTS];
  Vector2 output_point;
  float rotation;
  int connection_index;
  uint8_t text_size;
  uint8_t inputs;
  bool output;
  bool input_states[MAX_GATE_INPUTS];
  bool deleted;
  bool selected; // Perhaps merge with the wire selected array?
} BinaryGate;

#endif
