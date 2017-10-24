#include "text.h"
#include <string.h>
char* ab = " 0123456789ABCDEFGHIJKLMNOPQRSTUVXYZabcdefghijklmnopqrstuvwxyzàáèéìíòóùú&@#'(§!ç)°-_*$£%=+~:;.,?<>ÁÀÉÈÍÌÓÒÚÙâêîôûÂÊÎÔÛ€ãñöïëäüÿ";

void initTextRenderer(TextRenderer* tR,char* fontname,SDL_Renderer* rnd, int size, SDL_Color color){
    TTF_Init();
    TTF_Font* font = TTF_OpenFont(fontname,size);

    tR->clr = color;

    SDL_Surface* alphabet_surf = TTF_RenderText_Solid(font, ab, tR->clr);
    tR->chrSheet = SDL_CreateTextureFromSurface(rnd,alphabet_surf);

    int w,h;
    SDL_QueryTexture(tR->chrSheet, NULL, NULL, &w, &h);

    tR->chrW = 1+w/127;
    tR->chrH = h;
    tR->chrRect.x = 0;
    tR->chrRect.y = 0;
    tR->chrRect.w = w/127;
    tR->chrRect.h = h;

    SDL_FreeSurface(alphabet_surf);
    TTF_CloseFont(font);
    TTF_Quit();
}

//private function to find the character index:
//still inefficient, must be updated.

int pick(TextRenderer* tR,char c){
    for(int i=0;i<127;i++){
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
