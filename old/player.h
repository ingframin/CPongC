#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL2/SDL.h>
#include "utils.h"
typedef struct {
    SDL_Rect position;
    int speed;
    int tex_index;
    int score;
} Player;



void initPlayer(Player* p, int number, int speed, int tex_index);
void movePlayer(Player* p, Direction d);
void increaseScore(Player* p, int points);

#endif // PLAYER_H_INCLUDED
