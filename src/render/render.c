// render/render.c
#include "render.h"

void render_main(RenderContext* rc)
{
  wire_render(rc);
  gate_render(rc);
}
