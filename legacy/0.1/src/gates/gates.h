// gates/gates.h
#ifndef GATES_H
#define GATES_H

#include "raylib.h"

#include "../core.h"

// binary_gates_ui.c
void draw_binary_gates(ui_state* ui);
void create_gate(BinaryGateType type, Vector2 position);
void render_binary_gates();
const char* gate_type_to_string(BinaryGateType type);

// logic_binary.c
bit gate_not(bit a);
bit gate_and(bit a, bit b);
bit gate_nand(bit a, bit b);
bit gate_or(bit a, bit b);
bit gate_nor(bit a, bit b);
bit gate_xor(bit a, bit b);
bit gate_xnor(bit a, bit b);

// logic_ternary.c
trit gate_neg(trit a);
trit gate_min(trit a, trit b);
trit gate_max(trit a, trit b);
trit gate_consensus(trit a, trit b);

#endif
