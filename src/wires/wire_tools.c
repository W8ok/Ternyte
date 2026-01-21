// wires/wire_tools.c
#include <stdio.h>
#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


void SelectWires(Ui* ui, Circuit* cir, Wire wires[])
{
  // Deselect all
  if (ESCAPE_PRESSED)
  {
    for (int i = 0; i < cir->wire_count; i++)
    {
      wires[i].selected = false;
      wires[i].color = GREEN;
    }
    return;
  }

  bool is_in_workspace = CheckCollisionPointRec(ui->mouse_pos, ui->workspace_rec);
  
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace)
  {
    int clicked_wire = -1;
    
    for (int i = 0; i < cir->wire_count; i++)
    {
      if (CheckCollisionPointLine(ui->mouse_pos, wires[i].start, wires[i].end, GRID_SIZE / 2))
      {
        clicked_wire = i;
        break;
      }
    }

    if (clicked_wire < 0) 
      return; 

    // Select multiple
    if (SHIFT_PRESSED)
      wires[clicked_wire].selected = !wires[clicked_wire].selected;

    // Clear all and select only one
    else
      for (int i = 0; i < cir->wire_count; i++)
        wires[i].selected = (i == clicked_wire);
  }
}


void CutWires(Circuit* cir, Wire wires[])
{
  for (int i = 0; i < cir->wire_count; i++)
  {
    if (wires[i].selected)
    {
      wires[i].deleted = true;
      wires[i].selected = false;
    }
  }
}
