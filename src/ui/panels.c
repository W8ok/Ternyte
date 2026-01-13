// ui/panels.c
#include <stdio.h>
#include <math.h>

#include "../types.h"
#include "../gates/binary_gates_ui.h"
#include "raylib.h"

void draw_base_ui(ui_state* ui){

  // Main Panels
  ui->selectionPanel = (Rectangle){0, 0, ui->screenWidth / 5, ui->screenHeight};
  ui->workspace = (Rectangle){ui->selectionPanel.width, 0, ui->screenWidth - ui->selectionPanel.width, ui->screenHeight};

  DrawRectangleRec(ui->selectionPanel, DARKGRAY);
  DrawRectangleRec(ui->workspace, GRAY);
  
  // Seperator Lines
  DrawRectangle(ui->selectionPanel.width - SEPARATOR_THICKNESS, 0, SEPARATOR_THICKNESS, ui->screenHeight, BLACK);

  // Draw workspace gridlines
  for (int x = ui->selectionPanel.width + GRID_SIZE; x < ui->screenWidth; x += GRID_SIZE) {
    DrawLine(x, 0, x, ui->screenHeight, LIGHTGRAY);
  }   
  for (int y = GRID_SIZE; y < ui->screenHeight; y += GRID_SIZE) {
    DrawLine(ui->selectionPanel.width, y, ui->screenWidth, y, LIGHTGRAY);
  }
}


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


void draw_gate_selection(ui_state* ui, Tool* tool) {

  const char* gate_names[] = {"NOT", "AND", "OR", "XOR"};
  BinaryGateType gate_types[] = {NOT, AND, OR, XOR};
  int gate_count = sizeof(gate_names) / sizeof(*gate_names); 

  int button_height = 40;
  int padding = 10;
  
  for(int i = 0; i < gate_count; i++) {
    Rectangle button_rect;
    button_rect.x = ui->selectionPanel.x + padding;
    button_rect.y = ui->selectionPanel.y + padding + (i * (button_height + padding));
    button_rect.width = ui->selectionPanel.width - (padding * 2);
    button_rect.height = button_height;

    // Draw button
    Color button_color = CheckCollisionPointRec(GetMousePosition(), button_rect) ? (Color){100, 100, 100, 255} : DARKGRAY;
    DrawRectangleRec(button_rect, button_color);
    DrawRectangleLinesEx(button_rect, 2, BLACK);
    
    // Draw text centered
    int text_width = MeasureText(gate_names[i], 20);
    DrawText(gate_names[i], button_rect.x + (button_rect.width - text_width) / 2, button_rect.y + 10, 20, WHITE);
    
    // Handle click
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), button_rect)) {
      printf("Selected gate: %s\n", gate_names[i]);
      *tool = TOOL_COMPONENT;
      ui->selected_gate = gate_types[i];    // Store which gate we want
      ui->is_placing_gate = true;           // Set placement flag

      // Creates gate directly... chage this at somepoint perhaps?
      Vector2 mousePos = GetMousePosition();
      Vector2 snapped_pos = snap_to_grid(mousePos, ui->workspace, GRID_SIZE);
      create_gate(gate_types[i], snapped_pos);
    }
  }
}
