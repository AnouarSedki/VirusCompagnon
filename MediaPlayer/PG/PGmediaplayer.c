#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define IMAGE_COUNT 5
#define DISPLAY_TIME 2000  // Temps d'affichage par image (ms)

// Chemins des images dans le dossier "images/"
const char *image_files[IMAGE_COUNT] = {
    "images/image1.jpg",
    "images/image2.jpg",
    "images/image3.jpg",
    "images/image4.jpg",
    "images/image5.jpg"
};

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (!IMG_Init(IMG_INIT_JPG)) {
        printf("Erreur SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Media Player - Images",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur création fenêtre: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur création renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture* textures[IMAGE_COUNT];

    // Charger les images
    for (int i = 0; i < IMAGE_COUNT; i++) {
        SDL_Surface* surface = IMG_Load(image_files[i]);
        if (!surface) {
            printf("Erreur chargement %s: %s\n", image_files[i], IMG_GetError());
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    bool running = true;
    SDL_Event event;

    for (int i = 0; i < IMAGE_COUNT && running; i++) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textures[i], NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(DISPLAY_TIME);
    }

    // Nettoyage
    for (int i = 0; i < IMAGE_COUNT; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
