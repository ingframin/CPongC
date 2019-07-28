#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct{
    SDL_Window* wnd;
    SDL_Renderer* rnd;
    int width,height;
}Video;

Video* initVideo(const char* title,int width, int height);
void destroyVideo(Video* vd);

#endif