// ui/panels.c
#include "../types.h"
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
