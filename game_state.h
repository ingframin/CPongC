#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

//Handle game states, work in progress.
typedef enum{
    START_SCREEN, GAME, EXIT_SCREEN
}StateName;


typedef struct{
    StateName current;
    void (*init)(const char* title, int width, int height);
    void (*loop)(void);
    void (*quit)(void);
}State;

#endif // GAME_STATE_H_INCLUDED
