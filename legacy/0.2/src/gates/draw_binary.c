// gates/draw_binary.c
#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


const char* GateTypeToString(BinaryGate binary[], int i)
{
  switch(binary[i].type)
  {
    case GateInput:
      if (binary[i].output)
      {
        binary[i].color = GREEN;
        return "1";
      }
      binary[i].color = RED;
      return "0";
    case GateNOT: return "NOT";
    case GateAND: return "AND";
    case GateOR: return "OR";
    case GateXOR: return "XOR";
    default: return "UNKNOWN";
  }
}

void DefaultBinaryGateConfig(BinaryGate binary[], int i)
{
  switch (binary[i].type)
  {
    case GateInput:
      binary[i].inputs = 1;
      break;
    case GateAND:
      binary[i].color = DARKBLUE;
      binary[i].inputs = 2;
      break;
    case GateOR:
      binary[i].color = GREEN;
      binary[i].inputs = 2;
      break;
    case GateXOR:
      binary[i].color = PURPLE;
      binary[i].inputs = 2;
      break;
    case GateNOT:
      binary[i].color = RED;
      binary[i].inputs = 1;
      break;
    default:
      binary[i].color = BLACK;
      break;
  }
}


void DrawBinaryGates(Ui* ui, App* app, Circuit* cir, Wire wires[], BinaryGate binary[])
{
  if (ESCAPE_PRESSED)
    cir->gate_started = false;

  if (!cir->gate_started)
  {
    cir->is_placing_gate = false;
    return;
  }

  // Deselect all when starting a new gate
  for (int i = 0; i < cir->wire_count; i++)
    wires[i].selected = false;

  for (int i = 0; i < cir->gate_count; i++)
    binary[i].selected = false;

  binary[cir->gate_count].type = app->current_binary_type;
  binary[cir->gate_count].deleted = false;
  binary[cir->gate_count].selected = false;
  binary[cir->gate_count].output = false;
  binary[cir->gate_count].text_size = 20;

  DefaultBinaryGateConfig(binary, cir->gate_count);

  binary[cir->gate_count].gate_rec = (Rectangle){
    cir->snapped_pos.x,
    cir->snapped_pos.y,
    GRID_SIZE * 4,
    2 * GRID_SIZE + GRID_SIZE * binary[cir->gate_count].inputs
  };

  if (binary[cir->gate_count].type == GateInput || binary[cir->gate_count].inputs % 2)
    binary[cir->gate_count].gate_rec.height -= GRID_SIZE;

  cir->is_placing_gate = true;

  bool is_in_workspace = CheckCollisionPointRec(ui->mouse_pos, ui->workspace_rec);

  if (is_in_workspace)
  {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && cir->is_placing_gate)
      cir->gate_count++;

    // Preview Gate    
    for (int i = 0; i < binary[cir->gate_count].inputs; i++)
    {
      if (binary[i].type == GateInput)
        continue;

      binary[cir->gate_count].input_points[i] = (Vector2) {
        cir->snapped_pos.x,
        cir->snapped_pos.y + i * 2 * GRID_SIZE + GRID_SIZE
      };
      DrawCircleV(binary[cir->gate_count].input_points[i], GRID_SIZE / 4, BLACK);
    }

    DrawRectangleRec(binary[cir->gate_count].gate_rec, binary[cir->gate_count].color);
    DrawCircle(binary[cir->gate_count].gate_rec.x + binary[cir->gate_count].gate_rec.width, binary[cir->gate_count].gate_rec.y + binary[cir->gate_count].gate_rec.height / 2, GRID_SIZE / 4, BLACK);

    // Label the gates
    const char* label = GateTypeToString(binary, cir->gate_count);
    int text_width = MeasureText(label, binary[cir->gate_count].text_size);
    int text_x = binary[cir->gate_count].gate_rec.x + (binary[cir->gate_count].gate_rec.width - text_width) / 2;
    int text_y = binary[cir->gate_count].gate_rec.y + (binary[cir->gate_count].gate_rec.height - binary[cir->gate_count].text_size) / 2;
    DrawText(label, text_x, text_y, binary[cir->gate_count].text_size, WHITE);
  }
}


void RenderBinaryGates(Circuit* cir, BinaryGate binary[])
{
  for (int i = 0; i < cir->gate_count; i++)
  {
    if (binary[i].deleted)
      continue;
    
    for (int j = 0; j < binary[i].inputs; j++)
    {
      if (binary[i].type == GateInput)
        continue;

      binary[i].input_points[j] = (Vector2) {
        binary[i].gate_rec.x,
        binary[i].gate_rec.y + j * 2 * GRID_SIZE + GRID_SIZE
      };
      DrawCircleV(binary[i].input_points[j], GRID_SIZE / 4, BLACK);
    }

    Color output_color;

    if (binary[i].output)
      output_color = GREEN;
    else
      output_color = RED;

    DrawCircle(binary[i].gate_rec.x + binary[i].gate_rec.width, binary[i].gate_rec.y + binary[i].gate_rec.height / 2, GRID_SIZE / 4, output_color);

    if (binary[i].selected)
      binary[i].color = SELECTION_COLOR;
    else
      DefaultBinaryGateConfig(binary, i);

    DrawRectangleRec(binary[i].gate_rec, binary[i].color);

    // Label the gates
    const char* label = GateTypeToString(binary, i);
    int text_width = MeasureText(label, binary[i].text_size);
    int text_x = binary[i].gate_rec.x + (binary[i].gate_rec.width - text_width) / 2;
    int text_y = binary[i].gate_rec.y + (binary[i].gate_rec.height - binary[i].text_size) / 2;
    DrawText(label, text_x, text_y, binary[i].text_size, WHITE);
  }
}
