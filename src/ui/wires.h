// ui/wires.h
#ifndef WIRES_H
#define WIRES_H

#include "raylib.h"
#include "../types.h"
#include "../keybinds.h"

Vector2 snap_to_grid(Vector2 point, Rectangle workspace, int grid_size);
void draw_wires(ui_state* ui);
void render_wires();

#endif
