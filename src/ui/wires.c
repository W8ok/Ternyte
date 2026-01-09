// ui/wires.c
#include <math.h>
#include <stdio.h>

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

  if(ESCAPE_PRESSED) wire_started = false;

  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace){
    Vector2 snapped_pos;
    switch(wire_started){
      case false:
        snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
        wires[wire_count].start = snapped_pos;
        wires[wire_count].color = GREEN;
        wires[wire_count].deleted = false;
        wire_started = true;
        break;

      case true:
        snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);

        if(STRAIGHT){
          float dx = fabsf(wires[wire_count].start.x - snapped_pos.x);
          float dy = fabsf(wires[wire_count].start.y - snapped_pos.y);
          if(dx > dy) snapped_pos.y = wires[wire_count].start.y;
          else snapped_pos.x = wires[wire_count].start.x;
        }
        wires[wire_count].end = snapped_pos;

        undo_stack[undo_top++] = (undo_entry){
          .type = OP_ADD_WIRE,
          .wire_index = wire_count,
          .wire_state = wires[wire_count]  // Save current wire
        };
        wire_count++;

        // Chain wires
        wires[wire_count].start = snapped_pos;
        wires[wire_count].color = GREEN;
        wires[wire_count].deleted = false;
        break;
    }
  }
  
  // Preview wire
  if(wire_started) {
    Vector2 snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
    if(STRAIGHT){
      float dx = fabsf(wires[wire_count].start.x - snapped_pos.x);
      float dy = fabsf(wires[wire_count].start.y - snapped_pos.y);
      if(dx > dy) snapped_pos.y = wires[wire_count].start.y;
      else snapped_pos.x = wires[wire_count].start.x;
    }
    DrawLineEx(wires[wire_count].start, snapped_pos, WIRE_THICKNESS, RED);
  }
}


void render_wires(){
  for(int i = 0; i < wire_count; i++){
    if(wires[i].deleted) continue;
    DrawLineEx(wires[i].start, wires[i].end, WIRE_THICKNESS, wires[i].color);
  }
}

void select_wires(ui_state* ui) {
  Vector2 mousePos = GetMousePosition();
  bool is_in_workspace = CheckCollisionPointRec(mousePos, ui->workspace);
  
  // Escape: Deselect all
  if(ESCAPE_PRESSED) {
    for(int i = 0; i < wire_count; i++) {
      wires[i].selected = false;
      wires[i].color = GREEN;
    }
    return;
  }
  
  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && is_in_workspace) {
    int clicked_wire = -1;
    
    for(int i = 0; i < wire_count; i++) {
      if(CheckCollisionPointLine(mousePos, wires[i].start, wires[i].end, GRID_SIZE / 2)) {
        clicked_wire = i;
        break;
      }
    }
    if(clicked_wire < 0) return; 
    if(SHIFT_PRESSED) wires[clicked_wire].selected = !wires[clicked_wire].selected;
    else {
      // Clear all and select only one
      for(int i = 0; i < wire_count; i++) {
        wires[i].selected = (i == clicked_wire);
      }
    }
    
    // Update colors
    for(int i = 0; i < wire_count; i++) {
      wires[i].color = wires[i].selected ? BLUE : GREEN;
    }
  }
}

void cut_wires(){
  for (int i = 0; i < wire_count; i++) {
    if (wires[i].selected) {
      undo_stack[undo_top++] = (undo_entry){
        .type = OP_DELETE_WIRE,
        .wire_index = i,
        .wire_state = wires[i] // Copy before deletion
      };
      wires[i].deleted = true;
      wires[i].selected = false;
    }
  }
}
