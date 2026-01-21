// ui/panels.c
#include <stdio.h>
#include "raylib.h"

//#include "ui.h"
#include "../core.h"


void DrawBaseUi(AppState* ui)
{
  // Main Panels
  ui->selectionPanel = (Rectangle){0, 0, ui->screenWidth / 5, ui->screenHeight};
  ui->workspace = (Rectangle){ui->selectionPanel.width, 0, ui->screenWidth - ui->selectionPanel.width, ui->screenHeight};

  DrawRectangleRec(ui->selectionPanel, DARKGRAY);
  DrawRectangleRec(ui->workspace, GRAY);
  
  // Seperator Lines
  DrawRectangle(ui->selectionPanel.width - SEPARATOR_THICKNESS, 0, SEPARATOR_THICKNESS, ui->screenHeight, BLACK);

  // Draw workspace gridlines
  for (int x = ui->selectionPanel.width + GRID_SIZE; x < ui->screenWidth; x += GRID_SIZE)
  {
    DrawLine(x, 0, x, ui->screenHeight, LIGHTGRAY);
  }   

  for (int y = GRID_SIZE; y < ui->screenHeight; y += GRID_SIZE)
  {
    DrawLine(ui->selectionPanel.width, y, ui->screenWidth, y, LIGHTGRAY);
  }
}


// Please redo this, it sucks and is just horrid code idk :c
// I should never be allowed to do UI code again, what more proof do you need than what is going on below :3
int DrawGateSelection(AppState* ui, Tool* tool)
{
  const char* button_text[] = {"NOT", "AND", "OR", "XOR", "Input"};
  const int button_count = sizeof(button_text) / sizeof(*button_text); 
  Vector2 mouse_pos = GetMousePosition();

  BinaryGateType button_types[] = {NOT, AND, OR, XOR, INPUT};
  const int gate_count = sizeof(button_types) / sizeof(*button_types); 

  int button_height = 40;
  int button_spacing = 10;
  
  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rect;
    button_rect.x = ui->selectionPanel.x + button_spacing;
    button_rect.y = ui->selectionPanel.y + button_spacing + (i * (button_height + button_spacing));
    button_rect.width = ui->selectionPanel.width - (button_spacing * 2);
    button_rect.height = button_height;

    // Draw button
    Color button_color = CheckCollisionPointRec(GetMousePosition(), button_rect) ? GRAY : DARKGRAY;
    DrawRectangleRec(button_rect, button_color);
    DrawRectangleLinesEx(button_rect, 2, BLACK);
    
    // Draw text centered
    int text_width = MeasureText(button_text[i], 20);
    DrawText(button_text[i], button_rect.x + (button_rect.width - text_width) / 2, button_rect.y + 10, 20, WHITE);
    
    // Handle click
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse_pos, button_rect))
    {
      *tool = TOOL_COMPONENT;
      if(i < gate_count)
      {
        printf("Selected gate: %s\n", button_text[i]);
        ui->is_placing_gate = true;
        ui->selected_gate = button_types[i];
      }
    }
  }
}
