#ifndef __DISPLAY_H_INCLUDED_
#define __DISPLAY_H_INCLUDED_
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* wnd;
    SDL_Renderer* rnd;
    int width;
    int height;
} Display;

Display* newDisplay(const char* title, int width, int height);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);
//void renderDisplay(Display* disp, SDL_Texture** textures,SDL_Rect* positions, int n_objects);
void clearDisplay(Display* disp);

#endif