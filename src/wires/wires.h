// wires/wires.h
#ifndef WIRES_H
#define WIRES_H


#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


// draw_wires.c
void DrawWires(Ui* ui, Circuit* cir, Wire wires[], BinaryGate binary[]);
void RenderWires(Circuit* cir, Wire wires[]);

// wire_tools.c
void SelectWires(Ui* ui, Circuit* cir, Wire wires[]);
void CutWires(Circuit* cir, Wire wires[]);


#endif
