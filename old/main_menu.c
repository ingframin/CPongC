#include "main_menu.h"
#include "sprite.h"

void initMenu(Display* disp){
    StartGameButton = newSprite(disp->rnd,"textures/StartGame.png");
    QuitButton = newSprite(disp->rnd,"textures/Quit.png");
    moveSprite(StartGameButton,400,100);
    moveSprite(QuitButton,400,300);
}