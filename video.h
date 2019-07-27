#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
    SDL_Window* wnd;
    SDL_Renderer* rnd;
    
}Video;


#endif