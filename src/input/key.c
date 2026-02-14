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

    case SDLK_S: save_settings(&app->settings); break;
  }
}
