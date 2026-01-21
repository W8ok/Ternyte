// initialization.c
#include "stdlib.h"
#include "raylib.h"

#include "src.h"
#include "defines.h"
#include "types.h"

Vector2 mouse_pos;

void WindowInitialization(App* app, Ui* ui)
{
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(0, 0, "Ternyte");

  SetExitKey(KEY_NULL);
  SetTargetFPS(FPS);

  ui->monitor = GetCurrentMonitor();
  ui->screen_rec.width = GetMonitorWidth(ui->monitor);
  ui->screen_rec.height = GetMonitorHeight(ui->monitor);

  // Main Panels
  ui->selection_rec = (Rectangle){
    0,
    0,
    ui->screen_rec.width / 5,
    ui->screen_rec.height
  };

  ui->workspace_rec = (Rectangle){
    ui->selection_rec.width,
    0,
    ui->screen_rec.width - ui->selection_rec.width,
    ui->screen_rec.height
  };

  app->current_tool = OperateTool;
}

 
void CircuitInitialization(Circuit* cir, Move* move)
{
  cir->max_wires = 65535;
  cir->wire_count = 0;
  cir->wire_color = GREEN;
  cir->wire_started = false;

  cir->max_gates = 65535;
  cir->gate_count = 0;
  cir->gate_color = RED;
  cir->gate_started = false;

  move->moving = false;
  move->gate_start_pos = NULL;
  move->selected_indices = NULL;
  move->selection_count = 0;
}
