// save/settings.c
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <time.h>

#include "save.h"

bool make_circuit_snapshot(const LogicContext* lc, CircuitContext* cir)
{
  cir->gate_count = lc->gate_count;
  cir->wire_count = lc->wire_count;

  // Allocate memory and copy the arrays
  cir->gate = malloc(sizeof(Gates) * cir->gate_count);
  memcpy(cir->gate, lc->gate, sizeof(Gates) * cir->gate_count);

  cir->wire = malloc(sizeof(Wires) * cir->wire_count);
  memcpy(cir->wire, lc->wire, sizeof(Wires) * cir->wire_count);

  if (!cir->gate)
  {
    free(cir->wire);
    cir->wire = NULL;
    return false;
  }
  if (!cir->wire)
  {
    free(cir->gate);
    cir->gate = NULL;
    return false;
  }

  return true;
}

void free_circuit_snapshot(CircuitContext* cir)
{
  free(cir->gate);
  free(cir->wire);
  cir->gate = NULL;
  cir->wire = NULL;
}

bool save_circuit(CircuitContext* cir, AppSettings* settings)
{
  clock_t start = clock();

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushstring(L, settings->name);
  lua_setglobal(L, "name");
  
  lua_pushstring(L, settings->version);
  lua_setglobal(L, "version");

  lua_pushinteger(L, cir->gate_count);
  lua_setglobal(L, "gate_count");
  
  lua_pushinteger(L, cir->wire_count);
  lua_setglobal(L, "wire_count");

  // Wire table
  lua_newtable(L);
  for (int i = 0; i < cir->wire_count; i++) {
    lua_newtable(L);

    lua_pushinteger(L, cir->wire[i].x1);
    lua_setfield(L, -2, "x1");
    lua_pushinteger(L, cir->wire[i].y1);
    lua_setfield(L, -2, "y1");
    lua_pushinteger(L, cir->wire[i].x2);
    lua_setfield(L, -2, "x2");
    lua_pushinteger(L, cir->wire[i].y2);
    lua_setfield(L, -2, "y2");
    lua_pushinteger(L, cir->wire[i].connection_idx);
    lua_setfield(L, -2, "connection_idx");

    lua_rawseti(L, -2, i + 1);
  }
  lua_setglobal(L, "wires");

  // Gate table
  lua_newtable(L);
  for (int i = 0; i < cir->gate_count; i++) {
    lua_newtable(L);

    lua_pushinteger(L, cir->gate[i].x);
    lua_setfield(L, -2, "x");
    lua_pushinteger(L, cir->gate[i].y);
    lua_setfield(L, -2, "y");
    lua_pushinteger(L, cir->gate[i].rotation);
    lua_setfield(L, -2, "rotation");
    lua_pushinteger(L, cir->gate[i].type);
    lua_setfield(L, -2, "type");
    lua_pushinteger(L, cir->gate[i].output_idx);
    lua_setfield(L, -2, "output_idx");

    lua_newtable(L); // Input indices as a nested table
    for (int j = 0; j < MAX_GATE_INPUTS; j++)
    {
      lua_pushinteger(L, cir->gate[i].input_idx[j]);
      lua_rawseti(L, -2, j + 1);
    }
    lua_setfield(L, -2, "input_idx");

    lua_rawseti(L, -2, i + 1);
  }
  lua_setglobal(L, "gates");

  if (luaL_dofile(L, "src/save/save-circuit.lua") != LUA_OK)
  {
    const char* err = lua_tostring(L, -1);
    printf("Lua error (save-cir): %s\n", err);
    return false;
  }

  lua_close(L);
  free_circuit_snapshot(cir);

  printf("Save circuit time: %.3f ms\n", (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  return true;
}

bool clear_circuit(LogicContext* lc)
{
  if (lc->gate)
  {
    free(lc->gate);
    lc->gate = NULL;
  }
  if (lc->wire)
  {
    free(lc->wire);
    lc->wire = NULL;
  }
  
  // Round up to nearest 100 for cleaner allocation
  int gate_alloc = ((lc->gate_count + 99) / 100) * 100;
  int wire_alloc = ((lc->wire_count + 99) / 100) * 100;
  
  // Ensure at least 100 if count is 0
  if (gate_alloc == 0) gate_alloc = 100;
  if (wire_alloc == 0) wire_alloc = 100;

  lc->gate = (Gates *)calloc(gate_alloc, sizeof(Gates));
  lc->wire = (Wires *)calloc(wire_alloc, sizeof(Wires));

  if (!lc->gate)
  {
    printf("Failed to allocate gates for loading savefile\n");
    free(lc->wire);
    lc->wire = NULL;
    return false;
  }
  if (!lc->wire)
  {
    printf("Failed to allocate wires for loading savefile\n");
    free(lc->gate);
    lc->gate = NULL;
    return false;
  }
  return true;
}

// I have no clue how i wrote this in less than an hour...
// Mustve gotten so insane sleep or maybe autism simply locked in...
bool load_circuit(LogicContext* lc, AppSettings* settings)
{
  clock_t start = clock();

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // Error checking
  if (luaL_dofile(L, "src/save/load-circuit.lua") != LUA_OK)
  {
    const char *err = lua_tostring(L, -1);
    printf("Lua error (load-cir): %s\n", err);
    lua_close(L);
    return false;
  }

  // Version control
  lua_getglobal(L, "version");
  if (lua_isstring(L, -1))
  {
    size_t len;
    const char *ver = lua_tolstring(L, -1, &len);

    int x = 0, y = 0, z = 0;
    int px = 0, py = 0, pz = 0;
    
    if (sscanf(ver, "v%d.%d.%d", &x, &y, &z) != 3)
    {
      printf("Invalid version format: %s\n", ver);
      lua_close(L);
      return false;
    }
    sscanf(settings->version, "v%d.%d.%d", &px, &py, &pz);
    if (!(x == px) || y > py)
    {
      printf("Invalid version\n");
      return false;
    }

    for (int version_y = y; version_y < py; version_y++)
    {
      printf("Updating save to version: %d\n", version_y + 1); 
      switch (version_y)
      {
        // Update scripts
        case 0: 
          if (luaL_dofile(L, "src/save/upgrade_scripts/upgrade_to_1.lua") != LUA_OK)
          {
            printf("Upgrade failed: %s\n", lua_tostring(L, -1));
            lua_close(L);
            return false;
          }
          break;
        default: printf("No upgrade scripts available for version: %d\n", version_y); return false;
      }
    }
  }
  else
    return false;
  
  // If the program name is not the same return false
  lua_getglobal(L, "name");
  if (lua_isstring(L, -1))
  {
    size_t len;
    const char *name = lua_tolstring(L, -1, &len);

    if (len >= sizeof(settings->name))
    {
      lua_close(L);
      return false;
    }

    if (strcmp(name, settings->name) != 0)
    {
      lua_close(L);
      return false;
    }
  }
  else
    return false;
  lua_pop(L, 1);

  // Load the counts
  lua_getglobal(L, "gate_count");
  if (lua_isinteger(L, -1))
    lc->gate_count = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_getglobal(L, "wire_count");
  if (lua_isinteger(L, -1))
    lc->wire_count = lua_tointeger(L, -1);
  lua_pop(L, 1);

  clear_circuit(lc);

  // Push gates table onto stack
  lua_getglobal(L, "gates");
  if (!lua_istable(L, -1)) {
    printf("Error: gates is not a table\n");
    lua_close(L);
    return false;
  }

  for (int i = 0; i < lc->gate_count; i++) {
    lua_rawgeti(L, -1, i + 1);

    if (!lua_istable(L, -1)) {
      printf("Error: gate %d is not a table\n", i+1);
      lua_pop(L, 1);
      continue;
    }

    lua_getfield(L, -1, "x");
    lc->gate[i].x = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "y");
    lc->gate[i].y = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "rotation");
    lc->gate[i].rotation = (Rotation)lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "type");
    lc->gate[i].type = (GateType)lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "output_idx");
    lc->gate[i].output_idx = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "input_idx");
    if (lua_istable(L, -1))
    {
      for (int j = 0; j < MAX_GATE_INPUTS; j++)
      {
        lua_rawgeti(L, -1, j + 1);
        lc->gate[i].input_idx[j] = lua_tointeger(L, -1);
        lua_pop(L, 1);
      }
    }
    lua_pop(L, 1);

    lua_pop(L, 1);
  }
  // Pop gates table off stack
  lua_pop(L, 1);

  // Push wires table onto stack
  lua_getglobal(L, "wires");
  if (!lua_istable(L, -1)) {
    printf("Error: wires is not a table\n");
    lua_close(L);
    return false;
  }

  for (int i = 0; i < lc->wire_count; i++) {
    lua_rawgeti(L, -1, i + 1);

    if (!lua_istable(L, -1)) {
      printf("Error: wire %d is not a table\n", i+1);
      lua_pop(L, 1);
      continue;
    }

    lua_getfield(L, -1, "x1");
    lc->wire[i].x1 = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "y1");
    lc->wire[i].y1 = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "x2");
    lc->wire[i].x2 = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "y2");
    lc->wire[i].y2 = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "connection_idx");
    lc->wire[i].connection_idx = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pop(L, 1);
  }
  // Pop wires table off stack
  lua_pop(L, 1);

  lua_close(L);

  printf("Load circuit time: %.3f ms\n", (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  return true;
}
