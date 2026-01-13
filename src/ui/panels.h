// ui/panels.h
#ifndef PANELS_H
#define PANELS_H

#include "raylib.h"
#include "../types.h"

void draw_base_ui(ui_state* ui);
Vector2 snap_to_grid(Vector2 point, Rectangle workspace, int grid_size);
char draw_gate_selection(ui_state* ui, Tool* tool);

#endif
