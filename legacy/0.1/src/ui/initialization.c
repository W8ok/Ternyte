// ui/initialization.c
#include "raylib.h"

//#include "ui.h"
#include "../core.h"

void WindowInitialization(AppState* ui){
  // Initialization
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(0, 0, "Ternyte");

  ui->currentMonitor = GetCurrentMonitor();

  ui->screenWidth = GetMonitorWidth(ui->currentMonitor) * SCREEN_SIZE_FACTOR;
  ui->screenHeight = GetMonitorHeight(ui->currentMonitor) * SCREEN_SIZE_FACTOR;
  
  Vector2 monitorPos = GetMonitorPosition(ui->currentMonitor);
  
  ui->screenCenterX = monitorPos.x + (GetMonitorWidth(ui->currentMonitor) - ui->screenWidth) / 2;
  ui->screenCenterY = monitorPos.y + (GetMonitorHeight(ui->currentMonitor) - ui->screenHeight) / 2;

  SetWindowSize(ui->screenWidth, ui->screenHeight);
  SetWindowPosition(ui->screenCenterX, ui->screenCenterY);
  SetTargetFPS(FPS);
}
