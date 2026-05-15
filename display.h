#ifndef __DISPLAY_H_INCLUDED_
#define __DISPLAY_H_INCLUDED_
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
    SDL_Window* wnd;
    SDL_Renderer* rnd;
    int width;
    int height;
} Display;

typedef struct drawarray{
    SDL_Texture** textures;
    Uint32 drawarray_id;
    Uint16 current;
    Uint16 length;
}DrawArray;

Display* DISP_newDisplay(const char* title, int width, int height);
DrawArray* DISP_newDrawArray(SDL_Renderer* renderer, Uint16 length);
SDL_Texture* DISP_loadTexture(SDL_Renderer* renderer, const char* filename);
//void renderDisplay(Display* disp, SDL_Texture** textures,SDL_Rect* positions, int n_objects);
void clearDisplay(Display* disp);

#endif