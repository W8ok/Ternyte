// main.c
#define SDL_MAIN_USE_CALLBACKS true
#include <SDL3/SDL_main.h>
#include "main.h"

SDL_AppResult SDL_AppIterate(void *appstate)
{
  AppContext *app = (AppContext *)appstate;
  // Depending on the driver selected
  // it will change how the app updates behaves
  switch (app->driver)
  {
    case EVENT_DRIVEN:
      // Useless variable to make WaitEvent stfu and do what i want
      SDL_Event event;
      SDL_WaitEvent(&event);
      goto Iterate_Render;

    case REAL_TIME:
      // Temporary way to limit CPU from going brrrrr
      // Can be removed when the render core is in place
      SDL_Delay(100);
      goto Iterate_Render;

    default: goto Iterate_Continue;
  }

Iterate_Render:
  //render();

Iterate_Continue:
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  (void)appstate;
  if (event->type == SDL_EVENT_QUIT)
    return SDL_APP_SUCCESS;

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_Panic(const char* msg)
{
  const char* error = SDL_GetError();

  // If theres an error message, then print it
  if (error && error[0] != '\0')
    printf("Panic! %s: \t%s\n", msg, error);

  else
    printf("Panic! %s: \t(No Error Message)\n", msg);

  return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  (void)argc;
  (void)argv;

  AppContext default_app = {
    .name = "Ternyte",
    .version = "v0.0.1",
    .driver = REAL_TIME
  };

  // For saves make an "arena" memory for quicker access via cache
  AppContext *app = (AppContext *)SDL_calloc(1, sizeof(AppContext));
  *app = default_app;
  *appstate = app;

  if (!app)
    return SDL_Panic("AppContext memory allocation failed");

  // SDL stuff
  if(!SDL_Init(SDL_INIT_VIDEO))
    return SDL_Panic("SDL Initialization failed");

  // Get screen size
  SDL_DisplayID display = SDL_GetPrimaryDisplay();
  SDL_Rect display_bounds;
  if (!SDL_GetDisplayBounds(display, &display_bounds))
    return SDL_Panic("Display bounds not found");

  if (!SDL_SetAppMetadata(app->name, app->version, NULL))
    return SDL_Panic("Medadata creation failed");

  if (!SDL_CreateWindowAndRenderer(app->name, display_bounds.x, display_bounds.y, SDL_WINDOW_RESIZABLE, &app->window, &app->renderer))
    return SDL_Panic("Window/Renderer creation failed");

  if (SDL_RenderPresent(app->renderer))
    printf("Successfully opened the window\n");

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  AppContext *app = (AppContext *)appstate;

  if (result == SDL_APP_FAILURE)
    printf("Oopsie, i died! :3\n");
  else
    printf("I somehow didn't die! :D\n");

  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_free(app);
}
