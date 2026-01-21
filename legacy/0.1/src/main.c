// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "raylib.h"

#include "core.h"
//#include "ui/ui.h"
//#include "tools/tools.h" 
//#include "wires/wires.h"
//#include "gates/gates.h"
#include "keybinds.h"    

// Stopped refactoring cos bored :3
// Future me core.h is filled with stuff... spread it out to the other .h files
// Try and keep everything localized, and stuff that cant be use AppState
int main(void)
{
  // Initialization
  AppState app;
  Tool current_tool;
  current_tool = TOOL_SELECT;

  WindowInitialization(&app);
  SetExitKey(KEY_F4);

  // Main loop
  while (!WindowShouldClose())
  {
    current_tool = UpdateTool(current_tool);

    BeginDrawing();

    DrawBaseUi(&app);
    DrawGateSelection(&app, &current_tool);
    RenderWires();
    RenderBinaryGates();

    switch(current_tool)
    {
      case TOOL_SELECT:
        SelectWires(&app);
        if(CUT) CutWires();
        break;
      case TOOL_WIRE:
        DrawWires(&app);
        break;
      case TOOL_COMPONENT:
        if (app.is_placing_gate) DrawBinaryGates(&app);
        break;
    }

    // Global undo handling
    if(UNDO && undo_top > 0) Undo();

    ClearBackground(BLACK);

    EndDrawing(); 
  }
  CloseWindow();
  return 0;
}
