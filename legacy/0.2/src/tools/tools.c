// tools/tools.c
#include "raylib.h"

#include "../src.h"
#include "../defines.h"
#include "../types.h"


void SelectTools(App* app)
{
  if (S_PRESSED)
    app->current_tool = SelectTool;

  if (W_PRESSED)
    app->current_tool = WireTool;

  if (Q_PRESSED)
    app->current_tool = OperateTool;

  if (M_PRESSED)
    app->current_tool = MoveTool;
}
