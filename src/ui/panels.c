// ui/panels.c
#include <stdio.h>
#include "raylib.h"

#include "../defines.h"
#include "../types.h"

#include "ui.h"


void DrawBaseUi(Ui* ui)
{
  DrawRectangleRec(ui->selection_rec, DARKGRAY);
  DrawRectangleRec(ui->workspace_rec, GRAY);
  
  // Seperator Lines
  DrawRectangle(ui->selection_rec.width - SEPARATOR_THICKNESS, 0, SEPARATOR_THICKNESS, ui->screen_rec.height, BLACK);

  // Draw workspace gridlines
  for (int x = ui->selection_rec.width + GRID_SIZE; x < ui->screen_rec.width; x += GRID_SIZE)
    DrawLine(x, 0, x, ui->screen_rec.height, LIGHTGRAY); 

  for (int y = GRID_SIZE; y < ui->screen_rec.height; y += GRID_SIZE)
    DrawLine(ui->selection_rec.width, y, ui->screen_rec.width, y, LIGHTGRAY);
}
