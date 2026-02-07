// simulation.c
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

#include "src.h"
#include "defines.h"
#include "types.h"


void InitializeSimulation(App* app, Circuit* cir, Sim* sim, Wire wires[], BinaryGate binary[])
{
  //app->simulation_started = true;
  sim->contact_count = 0;

  for (int i = 0; i < cir->wire_count; i++)
  {
    if (wires[i].deleted)
      continue;

    for (int j = i+1; j < cir->wire_count; j++)
    {
      if (wires[j].deleted || i == j)
        continue;

      if (CheckCollisionPointLine(wires[i].start, wires[j].start, wires[j].end, GRID_SIZE / 2) ||
          CheckCollisionPointLine(wires[i].end, wires[j].start, wires[j].end, GRID_SIZE / 2) ||
          CheckCollisionPointLine(wires[j].start, wires[i].start, wires[i].end, GRID_SIZE / 2) ||
          CheckCollisionPointLine(wires[j].end, wires[i].start, wires[i].end, GRID_SIZE / 2))
        sim->contact_count++;
    }
  }
}


