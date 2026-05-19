#ifndef __DISPLAY_H_INCLUDED_
#define __DISPLAY_H_INCLUDED_
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
} Display;



Display* DISP_newDisplay(const char* title, int width, int height);

SDL_Texture* DISP_loadTexture(Display* disp, const char* filename);

void DISP_clearDisplay(Display* disp);

void DISP_update(Display* disp);

void DISP_freeDisplay(Display* disp);
#endif