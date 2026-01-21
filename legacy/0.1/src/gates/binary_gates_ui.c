// gates/binary_gates_ui.c
#include <stdio.h>
#include "raylib.h"

//#include "gates.h"
#include "../core.h"
#include "../keybinds.h"

Vector2 size = (Vector2){GRID_SIZE * 2, GRID_SIZE};
BinaryGate binary_gates[MAX_GATES];
int gate_count = 0;


const char* GateTypeToString(BinaryGateType type)
{
  switch(type)
  {
    case NOT: return "NOT";
    case AND: return "AND";
    case OR: return "OR";
    case XOR: return "XOR";
    default: return "UNKNOWN";
  }
}


static BinaryGate get_gate_template(BinaryGateType type)
{
  BinaryGate template = {0};
  template.gate_type = type;
  template.selected = false;
  template.deleted = false;
  template.input1 = false;
  template.input2 = false;
  template.output = false;
  template.input1_gate_index = -1;
  template.input2_gate_index = -1;
  
  switch(type)
  {
    case NOT:
      template.size = (Vector2){GRID_SIZE*3, GRID_SIZE*2};
      template.color = RED;
      break;
    case AND:
      template.size = (Vector2){GRID_SIZE*3, GRID_SIZE*2};
      template.color = BLUE;
      break;
    case OR:
      template.size = (Vector2){GRID_SIZE*3, GRID_SIZE*2};
      template.color = GREEN;
      break;
    case XOR:
      template.size = (Vector2){GRID_SIZE*3, GRID_SIZE*2};
      template.color = PURPLE;
      break;
  }
  return template;
}


void CreateGate(BinaryGateType type, Vector2 position)
{  
  BinaryGate new_gate = get_gate_template(type);
  new_gate.position = position;
  
  // Copy the gate instance to the array
  binary_gates[gate_count] = new_gate;
}


void DrawBinaryGates(AppState* ui)
{
  if(!ui->is_placing_gate) return;

  if(ESCAPE_PRESSED) ui->is_placing_gate = false;

  Vector2 mousePos = GetMousePosition();
  Vector2 snapped_pos = SnapToGrid(mousePos, ui->workspace, GRID_SIZE);
  
  // Draw preview
  BinaryGate preview = get_gate_template(ui->selected_gate);
  preview.position = snapped_pos;
  preview.color.a = 128;  // 50% transparent
  DrawRectangleV(preview.position, preview.size, preview.color);
  
  // Draw label
  const char* label = GateTypeToString(ui->selected_gate);
  int text_width = MeasureText(label, 20);
  int text_x = preview.position.x + (preview.size.x - text_width) / 2;
  int text_y = preview.position.y + (preview.size.y - 20) / 2;
  DrawText(label, text_x, text_y, 20, WHITE);
  
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, ui->workspace))
  {
    CreateGate(ui->selected_gate, snapped_pos);
    gate_count++; 
  }
}


// Replace this to actually make the gates not rectangles but real "sprites"
void RenderBinaryGates(void)
{
  for(int i = 0; i < gate_count; i++)
  {
    if(binary_gates[i].deleted) continue;

    DrawRectangleV(binary_gates[i].position, binary_gates[i].size, binary_gates[i].color);
    
    const char* label = GateTypeToString(binary_gates[i].gate_type);
    int text_width = MeasureText(label, 20);
    int text_x = binary_gates[i].position.x + (binary_gates[i].size.x - text_width) / 2;
    int text_y = binary_gates[i].position.y + (binary_gates[i].size.y - 20) / 2;
    DrawText(label, text_x, text_y, 20, WHITE);
  }
}
