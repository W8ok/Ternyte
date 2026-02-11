// rendering/colors.h
#pragma once

#include <SDL3/SDL.h>

// Grayscale
#define WHITE        ((SDL_Color){255, 255, 255, 255})
#define LIGHT_GRAY   ((SDL_Color){192, 192, 192, 255})
#define GRAY         ((SDL_Color){128, 128, 128, 255})
#define DARK_GRAY    ((SDL_Color){64,  64,  64, 255})
#define BLACK        ((SDL_Color){0,   0,   0, 255})

// Primary colors
#define RED          ((SDL_Color){255, 0,   0, 255})
#define GREEN        ((SDL_Color){0,   255, 0, 255})
#define BLUE         ((SDL_Color){0,   0, 255, 255})

// Secondary colors
#define YELLOW       ((SDL_Color){255, 255, 0, 255})
#define CYAN         ((SDL_Color){0, 255, 255, 255})
#define MAGENTA      ((SDL_Color){255, 0, 255, 255})

// Common UI colors
#define ORANGE       ((SDL_Color){255, 165, 0, 255})
#define PURPLE       ((SDL_Color){128, 0, 128, 255})
#define BROWN        ((SDL_Color){165, 42, 42, 255})
#define PINK         ((SDL_Color){255, 192, 203, 255})
#define LIGHT_BLUE   ((SDL_Color){173, 216, 230, 255})
#define DARK_BLUE    ((SDL_Color){0, 0, 139, 255})
#define LIGHT_GREEN  ((SDL_Color){144, 238, 144, 255})
#define DARK_GREEN   ((SDL_Color){0, 100, 0, 255})

