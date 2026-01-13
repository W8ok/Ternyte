// ui/wires.h
#ifndef WIRES_H
#define WIRES_H

#include "raylib.h"
#include "../types.h"
#include "../keybinds.h"

void draw_wires(ui_state* ui);
void render_wires();
void select_wires(ui_state* ui);
void cut_wires();

#endif
