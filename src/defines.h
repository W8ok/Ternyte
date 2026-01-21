// defines.h
#ifndef DEFINES_H
#define DEFINES_H


#define FPS 60

#define SEPARATOR_THICKNESS 3
#define GRID_SIZE 20

#define WIRE_THICKNESS 3
#define SELECTION_THICKNESS 3
#define SELECTION_COLOR ((Color){100, 190, 255, 128})
#define MAX_GATE_INPUTS 8


#define ESCAPE_PRESSED (IsKeyDown(KEY_ESCAPE))
#define SHIFT_PRESSED (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
#define CONTROL_PRESSED (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))

#define CUT (CONTROL_PRESSED && IsKeyPressed(KEY_X))

#define S_PRESSED (IsKeyPressed(KEY_S))
#define W_PRESSED (IsKeyPressed(KEY_W))
#define Q_PRESSED (IsKeyPressed(KEY_Q))
#define M_PRESSED (IsKeyPressed(KEY_M))


#endif
