// main.c
#include <stdio.h>
#include "raylib.h"

#include "src.h"
#include "defines.h"
#include "types.h"

#include "ui/ui.h"
#include "wires/wires.h"
#include "tools/tools.h"
#include "gates/gates.h"


int main(void)
{
  App app;
  Ui ui;
  Circuit cir;
  Move move;

  app.current_menu = BaseMenu;

  SetExitKey(KEY_NULL);
  WindowInitialization(&app, &ui);
  CircuitInitialization(&cir, &move);

  Wire wires[cir.max_wires];
  BinaryGate binary[cir.max_gates];

  while (!WindowShouldClose())
  {
    ui.mouse_pos = GetMousePosition();
    cir.snapped_pos = SnapToGrid(ui.mouse_pos, ui.workspace_rec, GRID_SIZE);
    SelectTools(&app);

    BeginDrawing();
    ClearBackground(BLACK);

    DrawBaseUi(&ui);
    RenderBinaryGates(&cir, binary);
    RenderWires(&cir, wires);

    // Tool Control
    switch (app.current_tool)
    {
      case OperateTool:
        OperateBinaryInputs(&ui, &cir, binary);
        break;
      case WireTool:
        DrawWires(&ui, &cir, wires, binary);
        break;
      case SelectTool:
        SelectWires(&ui, &cir, wires);
        SelectBinaryGates(&ui, &cir, binary);

        if (CUT)
        {
          CutWires(&cir, wires);
          CutGates(&cir, binary);
        }
        break;
      case GateTool:
        DrawBinaryGates(&ui, &app, &cir, wires, binary);
        break;
      case MoveTool:
        MoveGates(&app, &cir, &move, binary);
        break;
    }

    // Menu Control
    switch (app.current_menu)
    {
      case BaseMenu:
        BaseSelectionMenu(&ui, &app, &cir);
        break;
      case MenuMenu:
        BaseMenuMenu(&ui, &app);
        break;
    }

    if (app.should_quit)
      break;

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
