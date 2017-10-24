#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL2/SDL.h>
typedef struct {
    SDL_Rect position;
    int speed;
    int tex_index;
    int score;
} Player;

typedef enum{
    UP = -1,
    DOWN = 1
}Direction;

void initPlayer(Player* p, int number, int speed, int tex_index);
void movePlayer(Player* p, Direction d);
void increaseScore(Player* p, int points);

#endif // PLAYER_H_INCLUDED
