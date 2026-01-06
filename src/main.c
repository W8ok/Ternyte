// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "raylib.h"

#include "types.h"
#include "keybinds.h"
#include "gates/logic_binary.h"
#include "gates/logic_ternary.h"
#include "ui/initialization.h"
#include "ui/panels.h"
#include "ui/wires.h"

#include "tests/gate_tests.c"

Tool update_tool(Tool current_tool){
  if (KEY_SELECT_TOOL) return TOOL_SELECT;
  if (KEY_WIRE_TOOL) return TOOL_WIRE;

  return current_tool;
}

int main(void){

  // Initialization
  ui_state ui;
  Tool current_tool = TOOL_SELECT;

  window_initialization(&ui);

  // Main loop
  while (!WindowShouldClose()){

    current_tool = update_tool(current_tool);

    BeginDrawing();

    draw_base_ui(&ui);
    render_wires();

    switch(current_tool){
      case TOOL_SELECT:
        break;
      case TOOL_WIRE:
        draw_wires(&ui);
        break;
      case TOOL_COMPONENT:
        break;
    }

    ClearBackground(BLACK);

    EndDrawing(); 
  }
  CloseWindow();
  return 0;
}
