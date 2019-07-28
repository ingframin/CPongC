#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
    SDL_Texture* txt;
    SDL_Rect position;
}Sprite;


Sprite* newSprite(SDL_Renderer* rnd, const char* txt_path);
void freeSprite(Sprite* sprt);
void moveSprite(Sprite* sprt, int dx, int dy);

#endif