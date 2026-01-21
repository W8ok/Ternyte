// src.h
#ifndef SRC_H
#define SRC_H

#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

#include "types.h"


// initializatio.c
void WindowInitialization(App* app, Ui* ui);
void CircuitInitialization(Circuit* cir, Move* move);

// utilities.c
Vector2 SnapToGrid(Vector2 point, Rectangle workspace_rec, int grid_size);


#endif
