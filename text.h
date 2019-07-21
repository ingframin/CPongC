#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <SDL2/SDL.h>

typedef struct {
    int chrH;//Height of a char
    int chrW;//Width of a char
    SDL_Texture* chrSheet;//texture containing char sheet
    SDL_Rect chrRect;//the smallest rectangle that can contain a char
    SDL_Color clr;//the color used to render strings with this font

} TextRenderer;


void initTextRenderer(TextRenderer* tR, SDL_Renderer* rnd);

void write(TextRenderer* tR, SDL_Rect* pos,char* txt, SDL_Renderer* rnd);
#endif // TEXT_H_INCLUDED
