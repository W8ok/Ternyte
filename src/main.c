// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "raylib.h"

#include "types.h"
#include "keybinds.h"
#include "gates/logic_binary.h"
#include "gates/logic_ternary.h"
#include "gates/binary_gates_ui.h"
#include "ui/initialization.h"
#include "ui/panels.h"
#include "ui/wires.h"

#include "tests/gate_tests.c"


undo_entry undo_stack[MAX_UNDO];
int undo_top = 0;


Tool update_tool(Tool current_tool){
  if (KEY_SELECT_TOOL) return TOOL_SELECT;
  if (KEY_WIRE_TOOL) return TOOL_WIRE;
  if (KEY_COMPONENT_TOOL) return TOOL_COMPONENT;

  return current_tool;
}

void undo(){
  undo_entry last = undo_stack[--undo_top];
   
  switch(last.type) {
    case OP_ADD_WIRE:
      wire_count--;
      break;
    case OP_DELETE_WIRE:
      wires[last.wire_index] = last.wire_state;
      break;
  }
}

int main(void){

  // Initialization
  ui_state ui;
  Tool current_tool;
  current_tool = TOOL_SELECT;

  window_initialization(&ui);
  SetExitKey(KEY_NULL);

  // Main loop
  while (!WindowShouldClose()){

    current_tool = update_tool(current_tool);

    BeginDrawing();

    draw_base_ui(&ui);
    draw_gate_selection(&ui, &current_tool);
    render_wires();
    render_binary_gates();

    switch(current_tool){
      case TOOL_SELECT:
        select_wires(&ui);
        if(CUT) cut_wires();
        break;
      case TOOL_WIRE:
        draw_wires(&ui);
        break;
      case TOOL_COMPONENT:
        draw_binary_gates(&ui);
        break;
    }

    // Global undo handling
    if(UNDO && undo_top > 0) undo();

    ClearBackground(BLACK);

    EndDrawing(); 
  }
  CloseWindow();
  return 0;
}
