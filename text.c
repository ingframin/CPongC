#include "text.h"
#include <string.h>


const char ab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,?:abcdefghijklmnopqrstuvwxyz0123456789ÁÉÍÓÚÑÜáéíóúñüÀÈÌÒÙàèìòùÂÊÎÔÛâêîôûÄËÏÖäëïöÇçÃãÕõ\0";

void TXT_initTextRenderer(TextRenderer* tR, Display* disp){

    tR->chrSheet = DISP_loadTexture(disp, "textures/font_atlas.png");

    float w, h;
    SDL_GetTextureSize(tR->chrSheet, &w, &h);

    tR->chrW = (int)(w / strlen(ab));  // Calculate cell width from texture
    tR->chrH = (int)h;
    tR->chrRect.x = 0;
    tR->chrRect.y = 0;
    tR->chrRect.w = tR->chrW;
    tR->chrRect.h = tR->chrH;

    // Initialize ASCII lookup table for O(1) character lookup
    for (int i = 0; i < 128; i++) tR->charToIndex[i] = -1;
    for (int i = 0; ab[i]; i++) {
        tR->charToIndex[(unsigned char)ab[i]] = i * tR->chrW;
    }

    
}

//Render a string on screen
void TXT_writeTxt(TextRenderer* tR, SDL_Rect* pos, const char* txt, Display* disp){
    int l = strlen(txt);
    SDL_FRect srcRect, dstRect;
    srcRect.h = tR->chrH;
    srcRect.w = tR->chrW;
    dstRect.h = pos->h;
    dstRect.w = pos->w;

    for(int i = 0; i < l; i++){
        srcRect.x = (float)tR->charToIndex[(unsigned char)txt[i]];
        srcRect.y = 0;
        dstRect.x = (float)(pos->x + i * pos->w);
        dstRect.y = (float)pos->y;
        SDL_RenderTexture(disp->renderer, tR->chrSheet, &srcRect, &dstRect);
    }

}

void TXT_freeTextRenderer(TextRenderer* tR) {
    if (tR->chrSheet) SDL_DestroyTexture(tR->chrSheet);
}
