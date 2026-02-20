// input/key.c
#include "input.h"

void key_main(AppContext* app, SDL_Keycode key)
{
  switch (key) 
  {
    case SDLK_F11:
      app->settings.fullscreen = !app->settings.fullscreen;
      if (!SDL_SetWindowFullscreen(app->window, app->settings.fullscreen))
        printf("Failed to set fullscreen");
      break;

    case SDLK_ESCAPE:
      app->lc->wire_started = false;
      break;

    case SDLK_TAB:
      app->terminal = true;
      break;

    case SDLK_F5: 
      save_settings(&app->settings);
      break;

    case SDLK_S:
      // Should perhaps make cir not part of app... but this is easier :3
      // Make make_circuit_snapshot return a struct pointer
      make_circuit_snapshot(app->lc, app->cir);
      save_circuit(app->cir, &app->settings);
      break;

    case SDLK_L:
      load_circuit(app->lc, &app->settings);
      break;
  }
}
