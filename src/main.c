// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "raylib.h"

#include "types.h"
#include "gates/logic_binary.h"
#include "gates/logic_ternary.h"

#include "tests/gate_tests.c"

#define SCREEN_SIZE_FACTOR 0.8
#define FPS 60
#define GRID_SIZE 20 // Pixels between the gridlines
#define SEPERATOR_THICKNESS 3 // Pixels thick
#define MAX_WIRES 65536

typedef struct{
  Rectangle selectionPanel;
  Rectangle workspace;
  int screenWidth;
  int screenHeight;
} ui_state;

void draw_base_ui(ui_state ui){

  // Main Panels
  ui.selectionPanel = (Rectangle){0, 0, ui.screenWidth / 5, ui.screenHeight};
  ui.workspace = (Rectangle){ui.selectionPanel.width, 0, ui.screenWidth - ui.selectionPanel.x, ui.screenHeight};

  DrawRectangleRec(ui.selectionPanel, DARKGRAY);
  DrawRectangleRec(ui.workspace, GRAY);
  
  // Seperator Lines
  DrawRectangle(ui.selectionPanel.width - SEPERATOR_THICKNESS, 0, SEPERATOR_THICKNESS, ui.screenHeight, BLACK);

  // Draw workspace gridlines
  for (int x = ui.selectionPanel.width + GRID_SIZE; x < ui.screenWidth; x += GRID_SIZE) {
    DrawLine(x, 0, x, ui.screenHeight, LIGHTGRAY);
  }   
  for (int y = GRID_SIZE; y < ui.screenHeight; y += GRID_SIZE) {
    DrawLine(ui.selectionPanel.width, y, ui.screenWidth, y, LIGHTGRAY);
  }
}

typedef struct{
  Vector2 start;
  Vector2 end;
} wire;

wire wires[MAX_WIRES];
int wire_count = 0;

void draw_wires(ui_state ui){
  Vector2 mousePos = GetMousePosition();

  static bool wire_started = false;

  // CheckCollisionPointRec(mousePos, ui.workspace isnt working :3
  // good luck future me im going to bed
  // https://www.raylib.com/cheatsheet/cheatsheet.html
  // Very useful ^
  if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, ui.workspace)){
    printf("clicked in workspace\n");
    if(wire_started == false){
      wires[wire_count].start = mousePos;
      wire_started = true;
      printf("wire started\n");
    }
    else{
      wires[wire_count].end = mousePos;
      wire_count++;
      wire_started = false;
      printf("wire ended\n");
    }
  }
  for(int i = 0; i < wire_count; i++){
    DrawLineV(wires[i].start, wires[i].end, GREEN);
    printf("drawing wire %d", i);
  }
  if (wire_started) {
    DrawLineV(wires[wire_count].start, mousePos, RED);
  }
}

int main(void){
  
  ui_state ui;

  // Initialization
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(0, 0, "Ternyte");

  int currentMonitor = GetCurrentMonitor();

  ui.screenWidth = GetMonitorWidth(currentMonitor) * SCREEN_SIZE_FACTOR;
  ui.screenHeight = GetMonitorHeight(currentMonitor) * SCREEN_SIZE_FACTOR;
  
  Vector2 monitorPos = GetMonitorPosition(currentMonitor);
  
  int screenCenterX = monitorPos.x + (GetMonitorWidth(currentMonitor) - ui.screenWidth) / 2;
  int screenCenterY = monitorPos.y + (GetMonitorHeight(currentMonitor) - ui.screenHeight) / 2;

  SetWindowSize(ui.screenWidth, ui.screenHeight);
  SetWindowPosition(screenCenterX, screenCenterY);
  SetTargetFPS(FPS);
  
  // Main loop
  while (!WindowShouldClose()){

    BeginDrawing();

    draw_base_ui(ui);
    draw_wires(ui);

    EndDrawing(); 
  }
  CloseWindow();
  return 0;
}
