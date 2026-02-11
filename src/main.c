// main.c
#define SDL_MAIN_USE_CALLBACKS true
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "main.h"

SDL_AppResult SDL_Panic(const char* msg)
{
  time_t t = time(NULL);
  struct tm* tm_info = localtime(&t);

  char time_buf[20];
  strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);

  const char* error = SDL_GetError();

  if (error && error[0] != '\0')
    printf("[%s] FATAL: Panic! %s:\t%s\n", time_buf, msg, error);
  else
    printf("[%s] FATAL: Panic! %s:\t(No Error Message)\n", time_buf, msg);

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

    case LOGIC_SIM:
      goto LBL_Logic;

    default: goto LBL_Continue;
  }

LBL_Logic:
  //logic_main(app->lc);

LBL_Render:
  if (!app->rc->window) 
    return SDL_Panic("Window is NULL and is thus dead");

  if (!app->rc->sdl_renderer || !sdl_renderer)
    return SDL_Panic("Renderer is NULL and is thus dead");

  render_main(app->rc);

  if (!SDL_RenderPresent(sdl_renderer))
    return SDL_Panic("Render present failed");

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
      case SDLK_F11:
        app->settings.fullscreen = !app->settings.fullscreen;
        if (!SDL_SetWindowFullscreen(app->window, app->settings.fullscreen))
          printf("Failed to set fullscreen");
        break;

      case SDLK_S: save_settings(&app->settings); break;
    }
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  (void)argc;
  (void)argv;

  // Just for OCD reasons
  printf("\n");

  // Allocate AppContext
  AppContext *app = (AppContext *)SDL_calloc(1, sizeof(AppContext));
  if (!app)
    return SDL_Panic("AppContext memory allocation failed");

  // Allocate RenderContext
  app->rc = (RenderContext *)SDL_calloc(1, sizeof(RenderContext));
  if (!app->rc)
    return SDL_Panic("RenderContext memory allocation failed");

  // Allocate LogicContext
  app->lc = (LogicContext *)SDL_calloc(1, sizeof(LogicContext));
  if (!app->lc)
    return SDL_Panic("LogicContext memory allocation failed");

// Initialize default settings
  app->settings = (AppSettings){
    .name = "Ternyte",
    .version = "v0.0.1",
    .fullscreen = false,
    .driver = REAL_TIME
  };

  // Load saved settings
  if (!load_settings(&app->settings))
    return SDL_Panic("Settings failed to load");

  *appstate = app;

  // SDL stuff
  if (!SDL_Init(SDL_INIT_VIDEO))
    return SDL_Panic("SDL Initialization failed");

  // Display Size
  SDL_DisplayID display = SDL_GetPrimaryDisplay();
  SDL_Rect display_bounds;
  if (!SDL_GetDisplayBounds(display, &display_bounds))
    return SDL_Panic("Display bounds not found");

  if (!SDL_SetAppMetadata(app->settings.name, app->settings.version, NULL))
    return SDL_Panic("Metadata creation failed");

  if (!SDL_CreateWindowAndRenderer(app->settings.name, display_bounds.x, display_bounds.y, SDL_WINDOW_RESIZABLE, &app->window, &app->renderer))
    return SDL_Panic("Window/Renderer creation failed");

  if (!SDL_RenderPresent(app->renderer))
    return SDL_Panic("Failed to present initial frame");
  printf("Successfully opened the window\n");

  if (!SDL_SetWindowFullscreen(app->window, app->settings.fullscreen))
    SDL_Panic("Failed to apply fullscreen");

  app->rc->window = app->window;
  app->rc->sdl_renderer = app->renderer;
  sdl_renderer = app->renderer;
  app->rc->lc = app->lc;

  // Testing only
  app->lc->gate = (Gates *)SDL_calloc(255, sizeof(Gates));
  for (int i = 0; i < 255; i++)
    app->lc->gate[i].size = 2;

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
  SDL_free(app->rc);
  SDL_free(app->lc->gate);
  SDL_free(app->lc);
  SDL_free(app);
}
