// ui/wires.c
#include <math.h>

#include "../types.h"
#include "../keybinds.h"
#include "raylib.h"

wire wires[MAX_WIRES];
int wire_count = 0;

Vector2 snap_to_grid(Vector2 point, Rectangle workspace, int grid_size) {
    // Adjust point relative to workspace
    float relative_x = point.x - workspace.x;
    float relative_y = point.y - workspace.y;
    
    // Find the nearest grid multiple
    float snapped_x = roundf(relative_x / grid_size) * grid_size;
    float snapped_y = roundf(relative_y / grid_size) * grid_size;
    
    // Add workspace offset back
    snapped_x += workspace.x;
    snapped_y += workspace.y;
    
    return (Vector2){snapped_x, snapped_y};
}

void draw_wires(ui_state* ui){
  Vector2 mousePos = GetMousePosition();

  static bool wire_started = false;
  bool is_in_workspace = CheckCollisionPointRec(mousePos, ui->workspace);

  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace){
    if(wire_started == false){
      Vector2 snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
      wires[wire_count].start = snapped_pos;
      wire_started = true;
    }
    else{
      Vector2 snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
      wires[wire_count].end = snapped_pos;
      wire_count++;
      wire_started = false;
    }
  }
  
  // Preview wire
  if(wire_started) {
    Vector2 snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
    DrawLineEx(wires[wire_count].start, snapped_pos, WIRE_THICKNESS, RED);
  }
  if(UNDO && wire_count > 0){
    wire_count--;
  }
}
// Next task: Get wires to be selectable and deletable arbitrarily
void render_wires(){
  for(int i = 0; i < wire_count; i++){
    DrawLineEx(wires[i].start, wires[i].end, WIRE_THICKNESS, GREEN);
  }
}
