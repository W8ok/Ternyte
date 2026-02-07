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

        for (int i = 0; i < cir->wire_count; i++)
        {
          if (wires[i].deleted)
            continue;

          if (CheckCollisionPointLine(wires[cir->wire_count].start, wires[i].start, wires[i].end, GRID_SIZE / 2))
          {
            wires[cir->wire_count].connection_index = wires[i].connection_index;
            cir->got_indexed = true;
            break;
          }
        }

        if (!cir->got_indexed)
          wires[cir->wire_count].connection_index = cir->next_connection_index;

        printf("Connection Index: %d\t%b\n", wires[cir->gate_count].connection_index, cir->got_indexed);
        break;
      case true:
        float dx = fabsf(wires[cir->wire_count].start.x - cir->snapped_pos.x);
        float dy = fabsf(wires[cir->wire_count].start.y - cir->snapped_pos.y);

        if(dx > dy)
          cir->snapped_pos.y = wires[cir->wire_count].start.y;
        else 
          cir->snapped_pos.x = wires[cir->wire_count].start.x;

        wires[cir->wire_count].end = cir->snapped_pos;

        for (int i = 0; i < cir->wire_count; i++)
        {
          if (wires[i].deleted)
            continue;

          if (CheckCollisionPointLine(wires[cir->wire_count].end, wires[i].start, wires[i].end, GRID_SIZE / 2))
          {
            wires[cir->wire_count].connection_index = wires[i].connection_index;
            cir->got_indexed = true;
            break;
          }
        }

        if (!cir->got_indexed)
          cir->next_connection_index++;

        cir->wire_count++;

        // Chain wires
        wires[cir->wire_count].start = cir->snapped_pos;
        wires[cir->wire_count].color = cir->wire_color;
        wires[cir->wire_count].deleted = false;
        wires[cir->wire_count].selected = false;
        wires[cir->wire_count].state = false;
        wires[cir->wire_count].connection_index = wires[cir->wire_count-1].connection_index;
        printf("Connection Index: %d\t%b\n", wires[cir->gate_count].connection_index, cir->got_indexed);
        break;

        // Future me idk trying to get connection_indecies to work and its not going great
        // it works so long as the chain wire thingy doest go off for some reason... idk why :3
    }
  }

  // Preview wire
  if (cir->wire_started)
  {
    float dx = fabsf(wires[cir->wire_count].start.x - cir->snapped_pos.x);
    float dy = fabsf(wires[cir->wire_count].start.y - cir->snapped_pos.y);

    if (dx > dy)
      cir->snapped_pos.y = wires[cir->wire_count].start.y;
    else
      cir->snapped_pos.x = wires[cir->wire_count].start.x;

    DrawLineEx(wires[cir->wire_count].start, cir->snapped_pos, WIRE_THICKNESS, BLACK);
  }
  cir->got_indexed = false;
}


void RenderWires(Circuit* cir, Wire wires[])
{
  // Placed wires
  for (int i = 0; i < cir->wire_count; i++)
  {
    if (wires[i].deleted)
      continue;

    if (wires[i].selected)
      wires[i].color = SELECTION_COLOR;
    else
      wires[i].color = wires[i].state ? GREEN : RED;

    DrawLineEx(wires[i].start, wires[i].end, WIRE_THICKNESS, wires[i].color);
  }
}
