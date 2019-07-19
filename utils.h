#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum{
    UP = -1,
    DOWN = 1,
    LEFT,
    RIGHT
}Direction;

typedef struct {
    SDL_Point* points;
    int numpoints;
    int lifetime;
    Direction d;
} Particles;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);
int checkCollision(SDL_Rect rect1,SDL_Rect rect2);
void clearScreen(SDL_Renderer* renderer);
Particles* genParticles(int x, int y,int numParticles, Direction d);
void killParticles(Particles* p);
void drawParticles(SDL_Renderer* rnd, Particles* p);


#endif // UTILS_H_INCLUDED
