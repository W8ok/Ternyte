// ui/ui.h
#ifndef UI_H
#define UI_H


#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


// panels.c
void DrawBaseUi(Ui* ui);

// menus.c
void DrawSelectionButtons(int i, const char **button_text, Ui* ui);
void BaseSelectionMenu(Ui* ui, App* app, Circuit* cir);
void BaseMenuMenu(Ui* ui, App* app);


#endif
