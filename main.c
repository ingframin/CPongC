#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "player.h"
#include "ball.h"
#include "utils.h"
#include "text.h"
#include "game_state.h"
#include "audio.h"

#define FPS_INTERVAL 1
#define WLIGTH_COUNTER_DEFAULT 30
#define FPS_120 8
#define FPS_100 9
#define FPS_60 15

//Window and renderer, init is in the corresponding function
SDL_Window* window;
SDL_Renderer* renderer;

//Window icon
SDL_Surface* icon;

//if running is 1, the game is running
int running = 1;

//Strutures and strings to render score on screen
TextRenderer txt;
SDL_Rect score_p1_rect = {0,0,26,26};
SDL_Rect score_p2_rect = {800-52,0,26,26};
char p1_score[255];
char p2_score[255];

//time step
Uint32 dt;

//texture batch
SDL_Texture* textures[5];

//Where are the sprites?
SDL_Rect WallRect1 = {0,0,800,25};
SDL_Rect WallRect2 = {0,575,800,25};
SDL_Rect Player1Name = {0,28,20,20};
SDL_Rect Player2Name = {640,28,20,20};
SDL_Rect FPSRect = {400,600-56,15,15};
SDL_Rect FPSStrRect = {330,600-56,15,15};
SDL_Rect Logo = {130,235,540,130};

char fps[10];
char *FPS_str = "FPS:";
Player* player1;
Player* player2;
Ball* ball;

//https://patrickdearteaga.com/
//Mix_Music *music;

int channel;

Audio audio;
int hit_sound;
int wall_hit_sound;
int music;
Particles* p = NULL;
Uint32 fps_frames = 0; //frames passed since the last recorded fps.
Uint32 fps_lasttime = 0; //the last recorded time.
Uint32 fps_current; //the current FPS.
int wlight_counter = WLIGTH_COUNTER_DEFAULT;//lighting effect on wall hit by the walls

SDL_GameController* controller;

void initGame(const char* title,int width,int height){
//Init SDL and the game state

    SDL_Init(SDL_INIT_EVERYTHING);
    /* if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(-1);
    } */

    window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height, SDL_WINDOW_SHOWN);
    /* if (window == NULL) {
        // Unrecoverable error, exit here.
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(-1);
    } */

    renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);
    /* if (renderer == NULL) {
        // Unrecoverable error, exit here.
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(-1);
    }  */ 

    IMG_Init(IMG_INIT_PNG);
    //printf("IMG_Init: %s\n", IMG_GetError());
    icon = IMG_Load("textures/icon.png");
    //printf("IMG_Load: %s\n", IMG_GetError());
    SDL_SetWindowIcon(window,icon);
    //Only 5 textures used
    textures[0] = loadTexture(renderer,"textures/ball.png");
    textures[1] = loadTexture(renderer,"textures/wall.png");
    textures[2] = loadTexture(renderer,"textures/player1.png");
    textures[3] = loadTexture(renderer,"textures/player2.png");
    textures[4] = loadTexture(renderer,"textures/logo.png");

    audio = initAudio(44100,AUDIO_S16SYS,2,2048,2,1);

    hit_sound = loadSound(&audio,"hit.wav");
    //printf("Mix_LoadWAV(\"hit.wav\"): %s\n", Mix_GetError());
    wall_hit_sound = loadSound(&audio,"wall_hit.wav");
    //printf("Mix_LoadWAV(\"wall_hit.wav\"): %s\n", Mix_GetError());
    music = loadMusic(&audio,"interstellar_odyssey_125.ogg");
    //printf("Mix_LoadWAV(\"music.wav\"): %s\n", Mix_GetError());

    //Check for joysticks
    /*This is a stub to test controller support.
    It needs to be fixed to support 2 controllers. */
    if( SDL_NumJoysticks() < 1 ){
        printf( "Warning: No joysticks connected!\n" );
    }
    for(int i= 0;i<SDL_NumJoysticks();i++){
        if(SDL_IsGameController(i)){
            controller= SDL_GameControllerOpen(i);
            break;
            }       
    }
    SDL_GameControllerEventState(SDL_ENABLE);

}
    

void render(){
        
        //rendering section
        clearScreen(renderer);
        
        
        //this will be the render function
        SDL_RenderCopy(renderer,textures[4], NULL, &Logo);
        SDL_RenderCopy(renderer,textures[1],NULL,&WallRect1);
        SDL_RenderCopy(renderer,textures[1],NULL,&WallRect2);
        
        SDL_RenderCopy(renderer,textures[player1->tex_index],NULL,&(player1->position));
        SDL_RenderCopy(renderer,textures[player2->tex_index],NULL,&(player2->position));
        SDL_RenderCopy(renderer,textures[ball->tex_index],NULL,&ball->rect);

        write(&txt,&score_p1_rect,p1_score,renderer);
        write(&txt,&score_p2_rect,p2_score,renderer);
        write(&txt,&Player1Name,"Player 1",renderer);
        write(&txt,&Player2Name,"Player 2",renderer);
        write(&txt,&FPSStrRect,FPS_str,renderer);
        itoa(fps_current,fps,10);
        write(&txt,&FPSRect,fps,renderer);
        //Careful with this! 
        if(p!=NULL){
            drawParticles(renderer,p);
            p->lifetime -= 1;
        }

        SDL_RenderPresent(renderer);

}


void gameLoop(){
    running = 1;
    SDL_Event evt;
    Direction pd1 = UP;
    Direction pd2 = DOWN;
    fps_lasttime = SDL_GetTicks();
    Uint32 time = SDL_GetTicks();
    
    while(running){

        SDL_PumpEvents();

        //get keyboard input
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        //player 2
        if(keys[SDL_SCANCODE_ESCAPE]){
                   running = 0;
               }
        
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
        if(SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_DOWN)){
            movePlayer(player1,DOWN);
            pd1 = DOWN;
            if(checkCollision(player1->position,WallRect2)){
                movePlayer(player1,UP);
                pd1 = UP;
                }
        }
        if(SDL_GameControllerGetButton(controller,SDL_CONTROLLER_BUTTON_DPAD_UP)){
            movePlayer(player1,UP);
            pd1 = UP;
            if(checkCollision(player1->position,WallRect1)){
                movePlayer(player1,DOWN);
                pd1 = DOWN;
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
            SDL_SetTextureColorMod(textures[1],255,255,255);
            SDL_SetTextureColorMod(textures[4],255,255,255);
            ball->y_speed = -(ball->y_speed);
            playSound(&audio,wall_hit_sound);
            

        }
        else{
            if(wlight_counter<=0){
                SDL_SetTextureColorMod(textures[1],125,125,125);
                SDL_SetTextureColorMod(textures[4],125,125,125);
                wlight_counter = WLIGTH_COUNTER_DEFAULT;
            }
            else{
                wlight_counter -= 1;
            }
        }

        if(checkCollision(ball->rect,player1->position)){
            ball->x_speed = -(ball->x_speed);
            ball->y_speed += pd1;
            
            playSound(&audio,hit_sound);
            //Generate particle effect
            p = genParticles(ball->rect.x,ball->rect.y,500,LEFT);

        }
        


        if(checkCollision(ball->rect,player2->position)){
            ball->x_speed = -(ball->x_speed);
            ball->y_speed += pd2;
            playSound(&audio,hit_sound);
           
            //Generate particle effect
            p = genParticles(ball->rect.x,ball->rect.y,500,RIGHT);

        }

        //Score update
		if(ball->rect.x <0){
			increaseScore(player2,1);
			initBall(ball,0,30);


		}else if(ball->rect.x > 800){
			increaseScore(player1,1);
			initBall(ball,0,30);
		}

        //check if particles are still alive
        if(p!=NULL && p->lifetime <= 0){
            killParticles(p);
            p = NULL;
        }

        //Convert scores to string
        snprintf(p1_score,200,"%d",player1->score);
        snprintf(p2_score,200,"%d",player2->score);

        render();

        //Temporary solution for testing
        if(player1->score >= 25){
            printf("Player 1 Wins!!");
            running = 0;
        }
        if(player2->score >= 25){
            printf("Player 2 Wins!!");
            running = 0;
        }

        //Limit framerate to 60fps
        
        fps_frames++;
        dt = SDL_GetTicks()-time;
        if(dt < FPS_100){
            SDL_Delay(FPS_100-dt);
        }
        if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
         {
            fps_lasttime = SDL_GetTicks();
            fps_current = fps_frames;
            fps_frames = 0;
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
    SDL_GameControllerClose(controller);
    quitAudio(&audio);
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
    initTextRenderer(&txt,renderer);

    Player p1;
    Player p2;
    Ball b;

    player1=&p1;
    player2=&p2;
    ball=&b;

    initPlayer(player1,1,8,2);
    initPlayer(player2,2,8,3);
    initBall(ball,0,30);
    
    changeMusicVolume(64);
    
    playMusic(&audio,music,true);
    main_state.loop();

    main_state.quit();

    return 0;
}
