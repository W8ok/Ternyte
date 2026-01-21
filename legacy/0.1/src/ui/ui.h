// ui/ui.h
#ifndef UI_H
#define UI_H

#include "raylib.h"

#include "../core.h"

// panels.c
void draw_base_ui(ui_state* ui);
Vector2 snap_to_grid(Vector2 point, Rectangle workspace, int grid_size);
char draw_gate_selection(ui_state* ui, Tool* tool);

// initialization.c
void window_initialization(ui_state* ui);

#endif
