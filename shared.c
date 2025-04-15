#define PI 3.14159265358979323846
#define WIDTH 960
#define HEIGHT 540

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Coordinate;

typedef struct {
    Coordinate pos;
    size_t size;
} history;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

int init() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("Error while initialisation");
        return 1;
    }

    // Création d'une fenêtre
    window = SDL_CreateWindow(
        "Spaceshooter",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

