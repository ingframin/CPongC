#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "display.h"

typedef struct {
    SDL_Texture* txt;
    SDL_FRect rectangle;
    bool to_draw;
}Sprite;

typedef struct drawarray{
    Sprite** sprites;
    Uint32 drawarray_id;
    Uint16 current;
    Uint16 length;
}DrawArray;

DrawArray* SPRT_newDrawArray(Display* disp, Uint16 length);
void SPRT_freeDrawArray(DrawArray* arr);
int SPRT_loadSpriteIntoDrawArray(Display* disp, DrawArray* arr, const char* txt_path);
Sprite* SPRT_getSpriteFromDrawArray(DrawArray* arr, Uint16 index);

Sprite* SPRT_newSprite(Display* disp, const char* txt_path);
void SPRT_freeSprite(Sprite* sprt);
void SPRT_moveSprite(Sprite* sprt, float dx, float dy);
void SPRT_moveSpriteAbs(Sprite* sprt, float x, float y);
void SPRT_drawSprite(Display* disp, Sprite* sprt);
void SPRT_drawDrawArray(Display* disp, DrawArray* arr);

#endif