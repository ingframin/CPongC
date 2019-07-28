#include "player.h"

void initPlayer(Player* p, int number, int speed, int tex_index){
    p->score = 0;
    p->speed = speed;
    p->tex_index = tex_index;
    if(number == 1){
        p->position.x = 0;
        p->position.y = 225;
        p->position.w = 20;
        p->position.h = 80;
    }else{
        p->position.x = 780;
        p->position.y = 225;
        p->position.w = 20;
        p->position.h = 80;
    }
}

void movePlayer(Player* p, Direction d){

    p->position.y += d*p->speed;
}

void increaseScore(Player* p, int points){
    p->score+=points;

}
