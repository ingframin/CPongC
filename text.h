#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <SDL3/SDL.h>
#include "display.h"

typedef struct {
    int chrH;//Height of a char
    int chrW;//Width of a char
    SDL_Texture* chrSheet;//texture containing char sheet
    SDL_Rect chrRect;//the smallest rectangle that can contain a char
    SDL_Color clr;//the color used to render strings with this font
    int charToIndex[128];//ASCII lookup table for O(1) character lookup

} TextRenderer;


void TXT_initTextRenderer(TextRenderer* tR, Display* disp);

void TXT_writeTxt(TextRenderer* tR, SDL_Rect* pos, const char* txt, Display* disp);

void TXT_freeTextRenderer(TextRenderer* tR);


#endif // TEXT_H_INCLUDED
