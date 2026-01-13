// gates/binary_gates_ui.h
#ifndef BINARY_GATES_UI_H
#define BINARY_GATES_UI_H

#include "../types.h"
#include "raylib.h"

void draw_binary_gates(ui_state* ui);
void create_gate(BinaryGateType type, Vector2 position);
void render_binary_gates();

const char* gate_type_to_string(BinaryGateType type);

#endif
