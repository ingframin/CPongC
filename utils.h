#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef enum {LEFT,RIGHT} ParticleDirection;
typedef struct {
    SDL_Point* points;
    int numpoints;
    int lifetime;
    ParticleDirection d;
} Particles;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);
int checkCollision(SDL_Rect rect1,SDL_Rect rect2);
void clearScreen(SDL_Renderer* renderer);
Particles* genParticles(int x, int y,int numParticles, ParticleDirection d);
void killParticles(Particles* p);
void drawParticles(SDL_Renderer* rnd, Particles* p);
//void render(SDL_Renderer* renderer, SDL_Texture* textures,int n_txt);

#endif // UTILS_H_INCLUDED
