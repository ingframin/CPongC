#include<stdio.h>
#include<stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "display.h"
#include "sprite.h"

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main(int argc, char** argv){

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetAppMetadata("CPongC3", "3.0", "eu.ingframin.cpongc3");    

    Display* disp = DISP_newDisplay("CpongC3",WIDTH,HEIGHT);
    DrawArray* drawarray = SPRT_newDrawArray(disp,6);
    int ball_idx = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/ball.png");
    int p1 = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/player1.png");
    int p2 = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/player2.png");
    int wall_up = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/wall.png");
    int wall_down = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/wall.png");
    int logo = SPRT_loadSpriteIntoDrawArray(disp,drawarray,"./textures/logo.png");
    
    SPRT_moveSpriteAbs(SPRT_getSpriteFromDrawArray(drawarray,ball_idx),(float)WIDTH/2,(float)HEIGHT/2);
    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
        DISP_clearDisplay(disp);
        SPRT_drawDrawArray(disp,drawarray);
        DISP_update(disp);
        
    }

    SPRT_freeDrawArray(drawarray);
    DISP_freeDisplay(disp);

    
    SDL_Quit();
    return 0;
}