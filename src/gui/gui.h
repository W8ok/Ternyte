// gui/gui.h
#pragma once

#include <SDL3/SDL.h>

#include "clay.h"
#include "../render/render.h"

typedef struct {
  RenderContext* rc;
} UiContext;

void ui_grid(UiContext* uc, int cell_size);
void ui_main(UiContext* uc);
