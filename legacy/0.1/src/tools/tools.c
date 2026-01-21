// tools/tools.c
//#include "tools.h"
#include "../core.h"
#include "../keybinds.h"

undo_entry undo_stack[MAX_UNDO];
int undo_top = 0;


Tool UpdateTool(Tool current_tool)
{
  if (KEY_SELECT_TOOL) return TOOL_SELECT;
  if (KEY_WIRE_TOOL) return TOOL_WIRE;
  if (KEY_COMPONENT_TOOL) return TOOL_COMPONENT;

  return current_tool;
}


void Undo(void)
{
  undo_entry last = undo_stack[--undo_top];
   
  switch(last.type)
  {
    case OP_ADD_WIRE:
      wire_count--;
      break;
    case OP_DELETE_WIRE:
      wires[last.wire_index] = last.wire_state;
      break;
  }
}
