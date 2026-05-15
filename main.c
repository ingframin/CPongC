#include<stdio.h>
#include<stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "display.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main(int argc, char** argv){

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetAppMetadata("CPongC3", "3.0", "eu.ingframin.cpongc3");    

    Display* disp = DISP_newDisplay("CpongC3",WIDTH,HEIGHT);
    SDL_Texture* ball = DISP_loadTexture(disp->rnd, "./textures/ball.png");
    SDL_FRect ballrect = {WIDTH/2,HEIGHT/2,30.0,30.0};
    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        clearDisplay(disp);
        SDL_RenderTexture(disp->rnd,ball,NULL,&ballrect);
        SDL_RenderPresent(disp->rnd);
        
    }

    SDL_DestroyRenderer(disp->rnd);
    SDL_DestroyWindow(disp->wnd);

    
    SDL_Quit();
    return 0;
}