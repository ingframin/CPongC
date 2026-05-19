#include <stdint.h>
#include "stdlib.h"
#include "sprite.h"



// Simple 32-bit hash function for generating unique IDs
static Uint32 hash32(Uint32 x, Uint32 y) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x ^ ((y >> 16) ^ y);
}


Sprite* SPRT_newSprite(Display* disp, const char* txt_path){
    Sprite* sprt = (Sprite*)malloc(sizeof(Sprite));
    sprt->txt = DISP_loadTexture(disp, txt_path);
    float w, h;
    SDL_GetTextureSize(sprt->txt, &w, &h); 
    
    sprt->rectangle.x = 0.0f;
    sprt->rectangle.y = 0.0f;
    sprt->rectangle.w = w;
    sprt->rectangle.h = h;
    sprt->to_draw = true;
    return sprt;
}

DrawArray* SPRT_newDrawArray(Display* disp, Uint16 length){
    DrawArray* arr = (DrawArray*)malloc(sizeof(DrawArray));
    if (!arr) return NULL;
    
    arr->sprites = (Sprite**)calloc(length, sizeof(Sprite*));
    if (!arr->sprites) {
        free(arr);
        return NULL;
    }
    
    arr->current = 0;
    arr->length = length;
    arr->drawarray_id = hash32((Uint32)(uintptr_t)disp->renderer, (Uint32)length);
    
    return arr;
}

void SPRT_freeSprite(Sprite* sprt){
    SDL_DestroyTexture(sprt->txt);
    free(sprt);
}

void SPRT_freeDrawArray(DrawArray* arr){
    if (!arr) return;
    for (Uint16 i = 0; i < arr->length; i++) {
        if (arr->sprites[i]) {
            SPRT_freeSprite(arr->sprites[i]);
        }
    }
    free(arr->sprites);
    free(arr);
}

int SPRT_loadSpriteIntoDrawArray(Display* disp, DrawArray* arr, const char* txt_path){
    if (!arr || arr->current >= arr->length) return -1;
    Sprite* sprt = SPRT_newSprite(disp, txt_path);
    if (!sprt) return -1;
    int index = arr->current++;
    arr->sprites[index] = sprt;
    return index;
}

Sprite* SPRT_getSpriteFromDrawArray(DrawArray* arr, Uint16 index){
    if (!arr || index >= arr->length) return NULL;
    return arr->sprites[index];
}

void SPRT_moveSprite(Sprite* sprt, float dx, float dy){
    sprt->rectangle.x += dx;
    sprt->rectangle.y += dy;
}

void SPRT_moveSpriteAbs(Sprite* sprt, float x, float y){
    sprt->rectangle.x = x;
    sprt->rectangle.y = y;
}

void SPRT_drawSprite(Display* disp, Sprite* sprt){
    if (!sprt->to_draw) return;
    SDL_RenderTexture(disp->renderer, sprt->txt, NULL, &sprt->rectangle);
}

void SPRT_drawDrawArray(Display* disp, DrawArray* arr){
    if (!arr) return;
    for (Uint16 i = 0; i < arr->length; i++) {
        if (arr->sprites[i]) {
            SPRT_drawSprite(disp, arr->sprites[i]);
        }
    }
}