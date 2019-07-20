#include "ball.h"

void initBall(Ball* b,int tex_ind, int rad){
    //fixed for 800x600 window, it can be changed to handle different resolutions
    b->rect.x = 400;
    b->rect.y = 300;
    b->rect.w = rad;
    b->rect.h = rad;
    int dir = rand();
    b->tex_index = tex_ind;

    if(dir%2){
        b->x_speed = 5;
        b->y_speed = 0;
    }
    else{
        b->x_speed = -5;
        b->y_speed = 0;
    }


}

void moveBall(Ball* b,int xd, int yd){
    b->rect.x += xd*b->x_speed;
    b->rect.y += yd*b->y_speed;
}
