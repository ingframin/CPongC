#include "display.h"
#include "stdlib.h"
#include <stdint.h>

// Simple 32-bit hash function for generating unique IDs
static Uint32 hash32(Uint32 x, Uint32 y) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x ^ ((y >> 16) ^ y);
}

SDL_Texture* DISP_loadTexture(Display* disp, const char* filename){
    SDL_Texture* txt = IMG_LoadTexture(disp->renderer,filename);
    return txt;
}

Display* DISP_newDisplay(const char* title, int width, int height){
    Display* disp = (Display*)malloc(sizeof(Display));
    disp->window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
    disp->renderer = SDL_CreateRenderer(disp->window, NULL);
    disp->width = width;
    disp->height = height;
    return disp;
}



void DISP_clearDisplay(Display* disp){
    SDL_SetRenderDrawColor(disp->renderer,0,0,0,255);
    //Screen is black
    SDL_RenderClear(disp->renderer);

}

void DISP_update(Display* disp){
    SDL_RenderPresent(disp->renderer);
}

void DISP_freeDisplay(Display* disp){
    if (disp->renderer) SDL_DestroyRenderer(disp->renderer);
    if (disp->window) SDL_DestroyWindow(disp->window);
    free(disp);
}