#include "display.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename){
    SDL_Texture* txt;
    SDL_Surface* tmp = IMG_Load(filename);
    Uint32 colorkey = SDL_MapRGB( tmp->format, 100, 100, 100 );
    SDL_SetColorKey(tmp,SDL_TRUE,colorkey);
    txt = SDL_CreateTextureFromSurface(renderer,tmp);
    SDL_FreeSurface(tmp);
    return txt;
}

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