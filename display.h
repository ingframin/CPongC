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



Display* DISP_newDisplay(const char* title, int width, int height);

SDL_Texture* DISP_loadTexture(Display* disp, const char* filename);

void clearDisplay(Display* disp);

#endif