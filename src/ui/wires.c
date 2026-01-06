// ui/wires.c
#include "../types.h"
#include "raylib.h"

wire wires[MAX_WIRES];
int wire_count = 0;

void draw_wires(ui_state* ui){
  Vector2 mousePos = GetMousePosition();

  static bool wire_started = false;
  bool is_in_workspace = CheckCollisionPointRec(mousePos, ui->workspace);

  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace){
    if(wire_started == false){
      wires[wire_count].start = mousePos;
      wire_started = true;
    }
    else{
      wires[wire_count].end = mousePos;
      wire_count++;
      wire_started = false;
    }
  }
  for(int i = 0; i < wire_count; i++){
    DrawLineV(wires[i].start, wires[i].end, GREEN);
  }
  if (wire_started) {
    DrawLineV(wires[wire_count].start, mousePos, RED);
  }
}
