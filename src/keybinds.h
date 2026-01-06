// keybinds.h
#ifndef KEYBINDS_H
#define KEYBINDS_H

#include "raylib.h" 

// CTRL + Z
#define UNDO (IsKeyPressed(KEY_Z) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) 

// Tooling keybinds
#define KEY_WIRE_TOOL IsKeyPressed(KEY_W)
#define KEY_SELECT_TOOL IsKeyPressed(KEY_S)

#endif
