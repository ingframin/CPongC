#include "display.h"

Display* newDisplay(const char* title, int width, int height){
    Display* disp = (Display*)malloc(sizeof(Display));
    disp->wnd = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    disp->rnd = SDL_CreateRenderer(disp->wnd,0,SDL_RENDERER_ACCELERATED);
    disp->width = width;
    disp->height = height;
    return disp;
    
}

void clearDisplay(Display* disp){
    SDL_SetRenderDrawColor(disp->rnd,0,0,0,255);
    //Screen is black
    SDL_RenderClear(disp->rnd);

}