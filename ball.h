#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

typedef struct{
    SDL_Rect rect;
    int x_speed;
    int y_speed;
    int tex_index;

} Ball;

void initBall(Ball* b,int tex_ind);
void moveBall(Ball* b,int xs, int ys);

#endif // BALL_H_INCLUDED
