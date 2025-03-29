#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define LARGEUR 800
#define HAUTEUR 600
#define NB_IMAGES 5
#define BTN_L 100add 
#define BTN_H 50

const char *imgFichiers[NB_IMAGES] = {
"/Users/anouar/Documents/VirusCompagnon/MediaPlayer/images/image1.jpeg",
"/Users/anouar/Documents/VirusCompagnon/MediaPlayer/images/image2.jpeg",
"/Users/anouar/Documents/VirusCompagnon/MediaPlayer/images/image3.jpeg",
"/Users/anouar/Documents/VirusCompagnon/MediaPlayer/images/image4.jpg",
"/Users/anouar/Documents/VirusCompagnon/MediaPlayer/images/image5.jpg"
};

int main() {
  IMG_Init(IMG_INIT_JPG);

  SDL_Window* fen = SDL_CreateWindow("Images", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);
  SDL_Renderer* rendu = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture* tex[NB_IMAGES];
  for (int i = 0; i < NB_IMAGES; i++) {
    SDL_Surface* surf = IMG_Load(imgFichiers[i]);
    tex[i] = SDL_CreateTextureFromSurface(rendu, surf);
    SDL_FreeSurface(surf);
  }

  bool run = true;
  SDL_Event evt;
  int imgActu = 0;
  while (run) {
    while (SDL_PollEvent(&evt)) {
      if (evt.type == SDL_QUIT)
        run = false;
      else if (evt.type == SDL_KEYDOWN) {
        if (evt.key.keysym.sym == SDLK_RIGHT)
          imgActu = (imgActu + 1) % NB_IMAGES;
        else if (evt.key.keysym.sym == SDLK_LEFT)
          imgActu = (imgActu - 1 + NB_IMAGES) % NB_IMAGES;
      } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
        int x = evt.button.x, y = evt.button.y;
        if (x > 50 && x < 150 && y > HAUTEUR - 70 && y < HAUTEUR - 20)
          imgActu = (imgActu - 1 + NB_IMAGES) % NB_IMAGES;
        if (x > LARGEUR - 150 && x < LARGEUR - 50 && y > HAUTEUR - 70 && y < HAUTEUR - 20)
          imgActu = (imgActu + 1) % NB_IMAGES;
      }
    }
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, tex[imgActu], NULL, NULL);
    SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
    SDL_Rect btnPrec = {50, HAUTEUR - 70, BTN_L, BTN_H};
    SDL_Rect btnSuiv = {LARGEUR - 150, HAUTEUR - 70, BTN_L, BTN_H};
    SDL_RenderFillRect(rendu, &btnPrec);
    SDL_RenderFillRect(rendu, &btnSuiv);
    SDL_RenderPresent(rendu);
  }

  for (int i = 0; i < NB_IMAGES; i++)
    SDL_DestroyTexture(tex[i]);
  SDL_DestroyRenderer(rendu);
  SDL_DestroyWindow(fen);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
