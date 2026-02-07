// src.h
#ifndef SRC_H
#define SRC_H

#include <stdbool.h>
#include <stdint.h>
#include "raylib.h"

#include "types.h"


// initializatio.c
void WindowInitialization(App* app, Ui* ui);
void CircuitInitialization(Circuit* cir, Move* move, Sim* sim);

// utilities.c
Vector2 SnapToGrid(Vector2 point, Rectangle workspace_rec, int grid_size);

// Simulation
void InitializeSimulation(App* app, Circuit* cir, Sim* sim, Wire wires[], BinaryGate binary[]);

#endif
