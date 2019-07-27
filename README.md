# CPongC

Pong clone written in C and SDL2.

It requires GCC and SDL2.

A version of SDL2 (2.0.5) is included but I strongly suggest to download the last one from the website: www.libsdl.org.

All the credits and a huge thank you for SDL2 go to Sam Lantiga, the defunct Loki Software and all the development team.

## Controls

Player 1 moves with E and D, player 2 moves with the directional arrows Up and Down.
(I used E and D because they are in the same position on both AZERTY, QWERTZ and QUERTY keyboard). I do not have at the moment any plan to support other keyboard layouts.

## Build instructions

In order to build the project, run from the main folder:

c:\yourfolder\ > gcc main.c ball.c player.c text.c utils.c -L./SDL2/lib -I./SDL2/include/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o./bin/Debug/pong.exe -w -Wextra -Wfatal-errors -O3

On Linux and Mac OS, you can use the same command, just remove "-L./SDL2/lib -I./SDL2/include/ -lmingw32", you don't need this.
On Linux and Mac you need to install libSDL2-dev, libSDL2_image-dev, libSDL2_mixer-dev packages.
On Mac, you can install them with Homebrew or Mac Ports.
If you install them from the SDL2 website you need the -L/path/ and -I/path/ directives for gcc, pointing to the correct subfolders in the Framework folder.

The easiest is to edit the task.json file and use Visual Studio Code.
No editors war, if you like Vim, Emacs, Sublime, whatever, I don't care. My build is editor/ide agnostic.

## Additional information and license

If you need help, send me a message: framin2 at gmail.com.

I got the sounds and font for free. I added the font licence file in the fonts folder. The music comes from Patrick De Arteaga: <https://patrickdearteaga.com/>
He is awesome, visit his website and enjoy!
I made the sprites myself with Affinity Designer. They are a perfect example of programmer art :p
Feel free to reuse them at your will.

All my code is provided with BSD license.
