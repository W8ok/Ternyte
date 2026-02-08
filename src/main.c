// main.c
#define SDL_MAIN_USE_CALLBACKS true
#include <SDL3/SDL_main.h>

#include "main.h"
#include "saving/save.h"

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

SDL_AppResult SDL_AppIterate(void *appstate)
{
  AppContext *app = (AppContext *)appstate;
  // Depending on the driver selected
  // it will change how the app updates behaves
  switch (app->settings.driver)
  {
    case EVENT_DRIVEN:
      // Useless variable to make WaitEvent stfu and do what i want
      SDL_Event event;
      (void)event;
      SDL_WaitEvent(&event);
      goto LBL_Render;

    case REAL_TIME:
      goto LBL_Render;

    default: goto LBL_Continue;
  }

LBL_Render:
  //render();

  if (!SDL_RenderPresent(app->renderer))
    SDL_Panic("Render present failed\n");

LBL_Continue:
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  AppContext *app = (AppContext *)appstate;

  if (event->type == SDL_EVENT_QUIT)
    return SDL_APP_SUCCESS;

  if (event->type == SDL_EVENT_KEY_DOWN)
  {
    switch (event->key.key) 
    {
      case SDLK_S: save_settings(&app->settings); break;
      case SDLK_L: load_settings(&app->settings); break;
    }
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  (void)argc;
  (void)argv;

  // Allocate the AppContext
  AppContext *app = (AppContext *)SDL_calloc(1, sizeof(AppContext));
  if (!app)
    return SDL_Panic("AppContext memory allocation failed");

  // Initialize default settings
  app->settings = (AppSettings){
    .name = "Ternyte",
    .version = "v0.0.1",
    .fullscreen = false,
    .driver = REAL_TIME
  };

  *appstate = app;

  // SDL stuff
  if (!SDL_Init(SDL_INIT_VIDEO))
    return SDL_Panic("SDL Initialization failed");

  SDL_DisplayID display = SDL_GetPrimaryDisplay();
  SDL_Rect display_bounds;
  if (!SDL_GetDisplayBounds(display, &display_bounds))
    return SDL_Panic("Display bounds not found");

  if (!SDL_SetAppMetadata(app->settings.name, app->settings.version, NULL))
    return SDL_Panic("Metadata creation failed");

  if (!SDL_CreateWindowAndRenderer(app->settings.name, display_bounds.x, display_bounds.y,
                                   SDL_WINDOW_RESIZABLE, &app->window, &app->renderer))
    return SDL_Panic("Window/Renderer creation failed");

  if (SDL_RenderPresent(app->renderer))
    printf("Successfully opened the window\n");

  // Load saved settings
  //load_settings(&app->settings);

  return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  AppContext *app = (AppContext *)appstate;

  if (result == SDL_APP_FAILURE)
    printf("\nOopsie, i died! :3\n");
  else
    printf("\nI somehow didn't die! :D\n");

  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_free(app);
}
