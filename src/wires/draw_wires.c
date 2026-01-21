// wires/draw_wires.c
#include <math.h>
#include <stdio.h>
#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


void DrawWires(Ui* ui, Circuit* cir, Wire wires[], BinaryGate binary[])
{
  if (ESCAPE_PRESSED)
  {
    cir->wire_started = false;
    return;
  }

  bool is_in_workspace = CheckCollisionPointRec(ui->mouse_pos, ui->workspace_rec);

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace)
  {
    switch (cir->wire_started)
    {
      case false:
        wires[cir->wire_count].start = cir->snapped_pos;
        wires[cir->wire_count].color = cir->wire_color;
        wires[cir->wire_count].deleted = false;
        wires[cir->wire_count].selected = false;
        cir->wire_started = true;

        // Deselect all when starting new wire
        for (int i = 0; i < cir->wire_count-1; i++)
          wires[i].selected = false;

        for (int i = 0; i < cir->gate_count; i++)
          binary[i].selected = false;

        break;

      case true:
        if(CONTROL_PRESSED)
        {
          float dx = fabsf(wires[cir->wire_count].start.x - cir->snapped_pos.x);
          float dy = fabsf(wires[cir->wire_count].start.y - cir->snapped_pos.y);

          if(dx > dy)
            cir->snapped_pos.y = wires[cir->wire_count].start.y;
          else 
            cir->snapped_pos.x = wires[cir->wire_count].start.x;

          wires[cir->wire_count].end = cir->snapped_pos;
        }

        else
          wires[cir->wire_count].end = cir->snapped_pos;

        cir->wire_count++;

        // Chain wires
        wires[cir->wire_count].start = cir->snapped_pos;
        wires[cir->wire_count].color = cir->wire_color;
        wires[cir->wire_count].deleted = false;
        wires[cir->wire_count].selected = false;
        break;
    }
  }

  // Preview wire
  if (cir->wire_started)
  {
    if (CONTROL_PRESSED)
    { 
      float dx = fabsf(wires[cir->wire_count].start.x - cir->snapped_pos.x);
      float dy = fabsf(wires[cir->wire_count].start.y - cir->snapped_pos.y);

      if (dx > dy)
        cir->snapped_pos.y = wires[cir->wire_count].start.y;
      else
        cir->snapped_pos.x = wires[cir->wire_count].start.x;

      DrawLineEx(wires[cir->wire_count].start, cir->snapped_pos, WIRE_THICKNESS, BLACK);
    }

    else
      DrawLineEx(wires[cir->wire_count].start, cir->snapped_pos, WIRE_THICKNESS, BLACK);
  }
}


void RenderWires(Circuit* cir, Wire wires[])
{
  // Placed wires
  for (int i = 0; i < cir->wire_count; i++)
  {
    if (wires[i].deleted)
      continue;

    wires[i].color = wires[i].selected ? SELECTION_COLOR : GREEN;
    DrawLineEx(wires[i].start, wires[i].end, WIRE_THICKNESS, wires[i].color);
  }
}
