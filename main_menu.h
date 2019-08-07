#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "display.h"
#include "sprite.h"

Sprite* StartGameButton;
Sprite* QuitButton;

void initMenu(Display* disp);
#endif