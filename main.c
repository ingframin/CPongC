#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"
#include "ball.h"
#include "utils.h"
#include "text.h"
#include "game_state.h"

//Window and renderer, init is in the corresponding function
SDL_Window* window;
SDL_Renderer* renderer;

//Window icon
SDL_Surface* icon;

//if running is 1, the game is running
int running = 1;

//Strutures and strings to render score on screen
TextRenderer txt;
SDL_Rect score_p1_rect = {0,0,32,32};
SDL_Rect score_p2_rect = {800-64,0,32,32};
char p1_score[255];
char p2_score[255];

//time step
Uint32 dt;

//texture batchn ²,²
SDL_Texture* textures[4];

//Where are the sprites?
SDL_Rect WallRect1 = {0,0,800,25};
SDL_Rect WallRect2 = {0,575,800,25};
SDL_Rect BallRect = {100,100,25,25};
SDL_Rect Player1Name = {0,28,20,20};
SDL_Rect Player2Name = {640,28,20,20};
//Colors used for rendering
SDL_Color White = {255, 255, 255,255};
SDL_Color Shade = {255, 128, 10,255};

Player* player1;
Player* player2;
Ball* ball;

void initGame(const char* title,int width,int height){
//Init SDL and the game state
//Error checking is still missing

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);

    icon = IMG_Load("textures/icon.png");

    SDL_SetWindowIcon(window,icon);

    textures[0] = loadTexture(renderer,"textures/ball.png");
    textures[1] = loadTexture(renderer,"textures/wall.png");
    textures[2] = loadTexture(renderer,"textures/player1.png");
    textures[3] = loadTexture(renderer,"textures/player2.png");

}

void render(){
            //rendering section
        clearScreen(renderer);

        //this will be the render function
        SDL_RenderCopy(renderer,textures[1],NULL,&WallRect1);
        SDL_RenderCopy(renderer,textures[1],NULL,&WallRect2);
        SDL_RenderCopy(renderer,textures[ball->tex_index],NULL,&ball->rect);
        SDL_RenderCopy(renderer,textures[player1->tex_index],NULL,&(player1->position));
        SDL_RenderCopy(renderer,textures[player2->tex_index],NULL,&(player2->position));

        write(&txt,&score_p1_rect,p1_score,renderer);
        write(&txt,&score_p2_rect,p2_score,renderer);
        write(&txt,&Player1Name,"Player 1",renderer);
        write(&txt,&Player2Name,"Player 2",renderer);
        SDL_RenderPresent(renderer);

}


void gameLoop(){
    running = 1;
    SDL_Event evt;
    Direction pd1 = UP;
    Direction pd2 = DOWN;


    Uint32 time = SDL_GetTicks();

    while(running){

        SDL_PumpEvents();

        //get keyboard input
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        //player 2
        if(keys[SDL_SCANCODE_UP]){
            movePlayer(player2,UP);
            pd2 = UP;
            if(checkCollision(player2->position,WallRect1)){
                movePlayer(player2,DOWN);
                pd2 = DOWN;
            }
        }

        if(keys[SDL_SCANCODE_DOWN]){
            movePlayer(player2,DOWN);
            pd2 = DOWN;
            if(checkCollision(player2->position,WallRect2)){
                movePlayer(player2,UP);
                pd2 = UP;
            }
        }

        //Player 1
        if(keys[SDL_SCANCODE_E]){
            movePlayer(player1,UP);
            pd1 = UP;
            if(checkCollision(player1->position,WallRect1)){
                movePlayer(player1,DOWN);
                pd1 = DOWN;
            }
        }

        if(keys[SDL_SCANCODE_D]){
            movePlayer(player1,DOWN);
            pd1 = DOWN;
            if(checkCollision(player1->position,WallRect2)){
                movePlayer(player1,UP);
                pd1 = UP;
                }
        }

        //Other events
        while(SDL_PollEvent(&evt)){
            if(evt.type == SDL_QUIT){
                running = 0;
            }
        }//while

        //update ball position
        moveBall(ball,1,1);

        //Check collisions
        if(checkCollision(ball->rect,WallRect1)||checkCollision(ball->rect,WallRect2)){

            ball->y_speed = -(ball->y_speed);

        }

        if(checkCollision(ball->rect,player1->position)){
            ball->x_speed = -(ball->x_speed);

            ball->y_speed += pd1;

        }


        if(checkCollision(ball->rect,player2->position)){
            ball->x_speed = -(ball->x_speed);
            ball->y_speed += pd2;

        }

        //Score update
		if(ball->rect.x <0){
			increaseScore(player2,1);
			initBall(ball,0);


		}else if(ball->rect.x > 800){
			increaseScore(player1,1);

			initBall(ball,0);
		}

        //Convert scores to string
        snprintf(p1_score,200,"%d",player1->score);
        snprintf(p2_score,200,"%d",player2->score);

        render();

        //Limit framerate to 60fps
        dt = SDL_GetTicks()-time;

        if(dt < 15){
            SDL_Delay(15-dt);
        }

        time = SDL_GetTicks();
    }//big while
}//end gameloop function


void quitGame(){
    //Free memory

    for(int i=0;i<4;i++){
        SDL_DestroyTexture(textures[i]);
    }

    SDL_DestroyTexture(txt.chrSheet);

    //Quit modules
    TTF_Quit();
    IMG_Quit();
    SDL_FreeSurface(icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{

    State main_state;
    main_state.current = GAME;
    main_state.init = &initGame;
    main_state.loop = &gameLoop;
    main_state.quit = &quitGame;

    main_state.init("F Pong",800,600);

    //txt is global
    initTextRenderer(&txt,"fonts/Anonymous.ttf",renderer,60,White);

    Player p1;
    Player p2;
    Ball b;

    player1=&p1;
    player2=&p2;
    ball=&b;

    initPlayer(player1,1,5,2);
    initPlayer(player2,2,5,3);
    initBall(ball,0);
    main_state.loop();

    main_state.quit();

    return 0;
}
