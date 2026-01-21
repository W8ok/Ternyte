// keybinds.h
#ifndef KEYBINDS_H
#define KEYBINDS_H

#include "raylib.h" 


// CTRL + Z
#define UNDO (IsKeyPressed(KEY_Z) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))

// CTRL + X
#define CUT (IsKeyPressed(KEY_X) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))


// Tooling keybinds
#define KEY_WIRE_TOOL IsKeyPressed(KEY_W)
#define KEY_SELECT_TOOL IsKeyPressed(KEY_S)
#define KEY_COMPONENT_TOOL IsKeyPressed(KEY_C)

// Drawing keybinds
#define STRAIGHT (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))


// Key presses
//#define LEFT_CLICKED (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
//#define RIGHT_CLICKED (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
//#define MIDDLE_CLICKED (IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON))
#define ESCAPE_PRESSED (IsKeyDown(KEY_ESCAPE))
#define SHIFT_PRESSED (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))

#endif
