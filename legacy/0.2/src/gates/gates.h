// gates/gates.h
#ifndef GATES_H
#define GATES_H


#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


// draw_binary.c
void DrawBinaryGates(Ui* ui, App* app, Circuit* cir, Wire wire[], BinaryGate binary[]);
void RenderBinaryGates(Circuit* cir, BinaryGate binary[]);

// gate_tools.c
void SelectBinaryGates(Ui* ui, Circuit* cir, BinaryGate binary[]);
void CutGates(Circuit* cir, BinaryGate binary[]);
void OperateBinaryInputs(Ui* ui, Circuit* cir, BinaryGate binary[]);
void MoveGates(App* app, Circuit* cir, Move* move, BinaryGate binary[]);


#endif
