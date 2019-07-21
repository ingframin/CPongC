#include "display.h"

Display* newDisplay(const char* title, int width, int height){
    Display* disp = (Display*)malloc(sizeof(Display));
    disp->wnd = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    
}