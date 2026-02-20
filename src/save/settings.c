// save/settings.c
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <time.h>

#include "save.h"

bool save_settings(AppSettings* settings)
{
  clock_t start = clock();

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

  if (luaL_dofile(L, "src/save/save-settings.lua") != LUA_OK)
  {
    const char* err = lua_tostring(L, -1);
    printf("Lua error (save-set): %s\n", err);
    return false;
  }

  lua_close(L);

  printf("Save settings time: %.3f ms\n", (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  return true;
}

bool load_settings(AppSettings* settings)
{
  clock_t start = clock();
  
  // Checks if the file exists
  FILE *f = fopen("src/save/settings.racc", "r");
  if (!f)
    save_settings(settings);
  else
    fclose(f);

  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // Error checking
  if (luaL_dofile(L, "src/save/load-settings.lua") != LUA_OK)
  {
    const char *err = lua_tostring(L, -1);
    printf("Lua error (load-set): %s\n", err);
    lua_close(L);
    return false;
  }

  // If the program name is not the same return false
  lua_getglobal(L, "app_name");
  if (lua_isstring(L, -1))
  {
    size_t len;
    const char *s = lua_tolstring(L, -1, &len);

    if (len >= sizeof(settings->name))
    {
      lua_close(L);
      return false;
    }

    if (strcmp(s, settings->name) != 0)
    {
      lua_close(L);
      return false;
    }
  }
  lua_pop(L, 1);

  // Load the values
  lua_getglobal(L, "app_fullscreen");
  if (lua_isboolean(L, -1))
    settings->fullscreen = lua_toboolean(L, -1);
  lua_pop(L, 1);

  lua_getglobal(L, "app_driver");
  if (lua_isinteger(L, -1))
    settings->driver = (DriverID)lua_tointeger(L, -1);
  lua_pop(L, 1);

  lua_close(L);

  printf("Load settings time: %.3f ms\n", (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC);
  return true;
}

