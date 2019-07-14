#include "text.h"
#include <string.h>
char* ab = "0123456789";

void initTextRenderer(TextRenderer* tR, SDL_Renderer* rnd, SDL_Color color){
     
    tR->clr = color;

    SDL_Surface* alphabet_surf = IMG_Load("textures/font_tile_set.png");
    tR->chrSheet = SDL_CreateTextureFromSurface(rnd,alphabet_surf);

    int w,h;
    SDL_QueryTexture(tR->chrSheet, NULL, NULL, &w, &h);

    tR->chrW = w/10;
    tR->chrH = h;
    tR->chrRect.x = 0;
    tR->chrRect.y = 0;
    tR->chrRect.w = w/10;
    tR->chrRect.h = h;

    SDL_FreeSurface(alphabet_surf);
   
}

//private function to find the character index:
//still inefficient, must be updated.

int pick(TextRenderer* tR,char c){
    for(int i=0;i<10;i++){
        if(ab[i]==c){
            return i*tR->chrW;
        }
    }
    return -1;
}

//Render a string on screen
void write(TextRenderer* tR, SDL_Rect* pos,char* txt, SDL_Renderer* rnd){
    int l = strlen(txt);
    SDL_Rect rndRect = {pos->x,pos->y,pos->w,pos->h};
    for(int i =0;i<l;i++){
        tR->chrRect.x = pick(tR,txt[i]);
        SDL_RenderCopy(rnd,tR->chrSheet,&tR->chrRect,&rndRect);
        rndRect.x+=pos->w;
    }

}
