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

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename){
    SDL_Texture* txt = IMG_LoadTexture(renderer,filename);
    return txt;
}

Display* DISP_newDisplay(const char* title, int width, int height){
    Display* disp = (Display*)malloc(sizeof(Display));
    disp->wnd = SDL_CreateWindow("CPongC",width,height,SDL_WINDOW_OPENGL);
    disp->rnd = SDL_CreateRenderer(disp->wnd,NULL);
    disp->width = width;
    disp->height = height;
    return disp;
    
}

DrawArray* DISP_newDrawArray(SDL_Renderer* renderer, Uint16 length){
    DrawArray* arr = (DrawArray*)malloc(sizeof(DrawArray));
    if (!arr) return NULL;
    
    arr->textures = (SDL_Texture**)calloc(length, sizeof(SDL_Texture*));
    if (!arr->textures) {
        free(arr);
        return NULL;
    }
    
    arr->current = 0;
    arr->length = length;
    arr->drawarray_id = hash32((Uint32)(uintptr_t)renderer, (Uint32)length);
    
    return arr;
}

void clearDisplay(Display* disp){
    SDL_SetRenderDrawColor(disp->rnd,0,0,0,255);
    //Screen is black
    SDL_RenderClear(disp->rnd);

}