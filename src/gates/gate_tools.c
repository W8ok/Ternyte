// gates/gate_tools.c
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


void SelectBinaryGates(Ui* ui, Circuit* cir, BinaryGate binary[])
{
  // Deselect all
  if (ESCAPE_PRESSED)
  {
    for (int i = 0; i < cir->gate_count; i++)
      binary[i].selected = false;
    return;
  }

  bool is_in_workspace = CheckCollisionPointRec(ui->mouse_pos, ui->workspace_rec);
  
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace)
  {
    int clicked_gate = -1;
    
    for (int i = 0; i < cir->gate_count; i++)
    {
      if (CheckCollisionPointRec(ui->mouse_pos, binary[i].gate_rec))
      {
        clicked_gate = i;
        break;
      }
    }

    if (clicked_gate < 0) 
      return; 

    // Select multiple
    if (SHIFT_PRESSED)
      binary[clicked_gate].selected = !binary[clicked_gate].selected;

    // Clear all and select only one
    else
      for (int i = 0; i < cir->gate_count; i++)
        binary[i].selected = (i == clicked_gate);
  }
}


void CutGates(Circuit* cir, BinaryGate binary[])
{
  for (int i = 0; i < cir->gate_count; i++)
  {
    if (binary[i].selected)
    {
      binary[i].deleted = true;
      binary[i].selected = false;
    }
  }
}


void OperateBinaryInputs(Ui* ui, Circuit* cir, BinaryGate binary[])
{
  bool is_in_workspace = CheckCollisionPointRec(ui->mouse_pos, ui->workspace_rec);

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace)
    for (int i = 0; i < cir->gate_count; i++)
    {
      bool interract_with_gate = CheckCollisionPointRec(ui->mouse_pos, binary[i].gate_rec);

      if (binary[i].deleted)
        continue;

      if (interract_with_gate && binary[i].type == GateInput)
        binary[i].output = !binary[i].output;
    }
}


void MoveGates(App* app, Circuit* cir, Move* move, BinaryGate binary[])
{  
  // Initialize Moving Operation
  if (!move->moving)
  {
    move->selection_count = 0;

    for (int i = 0; i < cir->gate_count; i++)
      if (binary[i].selected && !binary[i].deleted)
        move->selection_count++;

    // Nothing selected
    if (move->selection_count == 0)
      return;

    move->gate_start_pos = malloc(move->selection_count * sizeof(Vector2));
    move->selected_indices = malloc(move->selection_count * sizeof(int));

    if (!move->gate_start_pos || !move->selected_indices)
    {
      free(move->gate_start_pos);
      free(move->selected_indices);
    
      return;
    }

    move->mouse_start_pos = cir->snapped_pos;
    move->moving = true;

    int j = 0;
    for (int i = 0; i < cir->gate_count; i++)
      if (binary[i].selected && !binary[i].deleted)
      {
        move->gate_start_pos[j] = (Vector2){binary[i].gate_rec.x, binary[i].gate_rec.y};
        move->selected_indices[j] = i;
        j++;
      }
  }

  // Move Gate Positions
  if (move->moving)
  {
    Vector2 delta = {cir->snapped_pos.x - move->mouse_start_pos.x, cir->snapped_pos.y - move->mouse_start_pos.y};
    
    for (int j = 0; j < move->selection_count; j++)
    {
      binary[move->selected_indices[j]].gate_rec.x = move->gate_start_pos[j].x + delta.x;
      binary[move->selected_indices[j]].gate_rec.y = move->gate_start_pos[j].y + delta.y;
    }
  }

  // Exit Move Tool
  if (move->moving && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || ESCAPE_PRESSED))
  {
    if (ESCAPE_PRESSED)
      for (int j = 0; j < move->selection_count; j++)
      {
        binary[move->selected_indices[j]].gate_rec.x = move->gate_start_pos[j].x;
        binary[move->selected_indices[j]].gate_rec.y = move->gate_start_pos[j].y;
        binary[move->selected_indices[j]].selected = false;
      }

    else
      for (int j = 0; j < move->selection_count; j++)
        binary[move->selected_indices[j]].selected = false;

    free(move->gate_start_pos);
    free(move->selected_indices);
    move->gate_start_pos = NULL;
    move->selected_indices = NULL;
    move->selection_count = 0;

    move->moving = false;
    app->current_tool = SelectTool;
    return;
  }
}
