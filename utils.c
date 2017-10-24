#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename){
    SDL_Texture* txt;
    SDL_Surface* tmp = IMG_Load(filename);
    Uint32 colorkey = SDL_MapRGB( tmp->format, 100, 100, 100 );
    SDL_SetColorKey(tmp,SDL_TRUE,colorkey);
    txt = SDL_CreateTextureFromSurface(renderer,tmp);
    SDL_FreeSurface(tmp);
    return txt;
}

int checkCollision(SDL_Rect rect1,SDL_Rect rect2){
    // Find edges of rect1
	int left1 = rect1.x;
	int right1 = rect1.x + rect1.w;
	int top1 = rect1.y;
	int bottom1 = rect1.y + rect1.h;

	// Find edges of rect2
	int left2 = rect2.x;
	int right2 = rect2.x + rect2.w;
	int top2 = rect2.y;
	int bottom2 = rect2.y + rect2.h;

	// Check edges
	if ( left1 > right2 )// Left 1 is right of right 2
		return 0; // No collision

	if ( right1 < left2 ) // Right 1 is left of left 2
		return 0; // No collision

	if ( top1 > bottom2 ) // Top 1 is below bottom 2
		return 0; // No collision

	if ( bottom1 < top2 ) // Bottom 1 is above top 2
		return 0; // No collision

    return 1;
}

void clearScreen(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    //Screen is black
    SDL_RenderClear(renderer);

}

