#include "sprite.h"
#include "utils.h"

Sprite* newSprite(SDL_Renderer* rnd, const char* txt_path){
    Sprite* sprt = (Sprite*)malloc(sizeof(Sprite));
    sprt->txt = loadTexture(rnd,txt_path);
    int w, h;
    SDL_QueryTexture(sprt->txt, NULL, NULL, &w, &h);

    sprt->position.x = 0;
    sprt->position.y = 0;
    sprt->position.w = w;
    sprt->position.h = h;
    return sprt;
}

void freeSprite(Sprite* sprt){
    SDL_DestroyTexture(sprt->txt);
    free(sprt);
}

void moveSprite(Sprite* sprt, int dx, int dy){
    sprt->position.x += dx;
    sprt->position.y += dy;
}