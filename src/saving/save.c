// save.c
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>

#include "../main.h"

void save_settings(AppSettings *settings)
{
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushstring(L, settings->name);
  lua_setglobal(L, "name");

  lua_pushstring(L, settings->version);
  lua_setglobal(L, "version");

  lua_pushboolean(L, settings->fullscreen);
  lua_setglobal(L, "fullscreen");

  lua_pushinteger(L, settings->driver);
  lua_setglobal(L, "driver");

  if (luaL_dofile(L, "src/saving/save-settings.lua") != LUA_OK)
  {
    const char *err = lua_tostring(L, -1);
    printf("Lua error (save): %s\n", err);
  }

  lua_close(L);
}

void load_settings(AppSettings *settings)
{
  
  FILE *f = fopen("src/saving/settings.racc", "r");
  if (!f)
    save_settings(settings);
  else
    fclose(f);

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "src/saving/load-settings.lua") != LUA_OK)
  {
    const char *err = lua_tostring(L, -1);
    printf("Lua error (load): %s\n", err);
    lua_close(L);
    return;
  }

  lua_getglobal(L, "app_name");
  if (lua_isstring(L, -1))
    snprintf(settings->name, sizeof(settings->name), "%s", lua_tostring(L, -1));
  lua_pop(L, 1);

  lua_getglobal(L, "app_version");
  if (lua_isstring(L, -1))
    settings->version = lua_tostring(L, -1);
  lua_pop(L, 1);

  lua_getglobal(L, "app_fullscreen");
  if (lua_isboolean(L, -1))
    settings->fullscreen = lua_toboolean(L, -1);
  lua_pop(L, 1);

  lua_getglobal(L, "app_driver");
  if (lua_isinteger(L, -1))
    settings->driver = (DriverID)lua_tointeger(L, -1);
  lua_pop(L, 1);

  lua_close(L);

  printf("Loaded settings:\n");
  printf("  name: %s\n", settings->name);
  printf("  version: %s\n", settings->version);
  printf("  fullscreen: %s\n", settings->fullscreen ? "true" : "false");
  const char* driver_str = settings->driver == REAL_TIME ? "REAL_TIME" :
                           settings->driver == EVENT_DRIVEN ? "EVENT_DRIVEN" : "UNKNOWN";
  printf("  driver: %s\n", driver_str);
}

