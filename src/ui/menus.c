// ui/menus.c
#include <stdio.h>
#include "raylib.h"

#include "../defines.h"
#include "../types.h"

#include "ui.h"


void DrawSelectionButtons(int i, const char **button_text, Ui* ui)
{
  int BUTTON_WIDTH = ui->selection_rec.width * 9 / 10;
  int BUTTON_HEIGHT = ui->selection_rec.height / 20;
  int BUTTON_SPACING = BUTTON_HEIGHT / 10;
  int TEXT_SIZE = BUTTON_HEIGHT * 4 / 5;

  ui->button_rec = (Rectangle){
    ui->selection_rec.width / 2 - BUTTON_WIDTH / 2,
    ui->selection_rec.y + (ui->selection_rec.width - BUTTON_WIDTH) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING),
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  };

  // Draw button
  ui->button_color = CheckCollisionPointRec(ui->mouse_pos, ui->button_rec) ? GRAY : DARKGRAY;
  DrawRectangleRec(ui->button_rec, ui->button_color);
  DrawRectangleLinesEx(ui->button_rec, 2, BLACK);
  
  // Draw text centered
  int text_width = MeasureText(button_text[i], TEXT_SIZE);
  int text_x = ui->button_rec.x + (ui->button_rec.width - text_width) / 2;
  int text_y = ui->button_rec.y + (ui->button_rec.height - TEXT_SIZE) / 2 + 4; // +4 because wierd offset idk
  
  DrawText(button_text[i], text_x, text_y, TEXT_SIZE, WHITE);
}


void BaseSelectionMenu(Ui* ui, App* app, Circuit* cir)
{
  const char* button_text[] = {"Menu", "Inputs", "AND", "OR", "XOR", "NOT"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);

  for (int i = 0; i < button_count; i++)
  {
    DrawSelectionButtons(i, button_text, ui);

    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(ui->mouse_pos, ui->button_rec))
      continue;

    switch ((BaseSelectionMenuButton)i)
    {
      case Menu:
        app->current_menu = MenuMenu;
        break;
      case Input:
        app->current_binary_type = GateInput;
        cir->gate_started = true;
        app->current_tool = GateTool;
        printf("Selected gate: Input\n");
        break;
      case AND:
        app->current_binary_type = GateAND;
        cir->gate_started = true;
        app->current_tool = GateTool;
        printf("Selected gate: AND\n");
        break;
      case OR:
        app->current_binary_type = GateOR;
        cir->gate_started = true;
        app->current_tool = GateTool;
        printf("Selected gate: OR\n");
        break;
      case XOR:
        app->current_binary_type = GateXOR;
        cir->gate_started = true;
        app->current_tool = GateTool;
        printf("Selected gate: XOR\n");
        break;
      case NOT:
        app->current_binary_type = GateNOT;
        cir->gate_started = true;
        app->current_tool = GateTool;
        printf("Selected gate: NOT\n");
        break;
    }
  }
}


void BaseMenuMenu(Ui* ui, App* app)
{
  const char* button_text[] = {"Back", "Quit"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);

  for (int i = 0; i < button_count; i++)
  {
    DrawSelectionButtons(i, button_text, ui);

    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(ui->mouse_pos, ui->button_rec))
      continue;

    switch ((BaseMenuMenuButton)i)
    {
      case Back:
        app->current_menu = BaseMenu;
        break;
      case Quit:
        app->should_quit = true;
        break;
    }
  }
}
