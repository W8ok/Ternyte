// wires/wires.h
#ifndef WIRES_H
#define WIRES_H

#include "raylib.h"

#include "../core.h"

// wires.c
void draw_wires(AppState* ui);
void render_wires(void);
void select_wires(AppState* ui);
void cut_wires(void);

#endif
