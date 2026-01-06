// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 
#include "raylib.h"

#include "types.h"
#include "gates/logic_binary.h"
#include "gates/logic_ternary.h"
#include "ui/initialization.h"
#include "ui/panels.h"
#include "ui/wires.h"

#include "tests/gate_tests.c"

int main(void){

  // Initialization
  ui_state ui;

  window_initialization(&ui);

  // Main loop
  while (!WindowShouldClose()){

    BeginDrawing();

    draw_base_ui(&ui);
    draw_wires(&ui);

    EndDrawing(); 
  }
  CloseWindow();
  return 0;
}
