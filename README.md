# CPongC
Pong clone written in C and SDL2.

It requires GCC and SDL2.

A version of SDL2 (2.0.5) is included but I strongly suggest to download the last one from the website: www.libsdl.org.

All the credits and a huge thank you for SDL2 go to Sam Lantiga, the defunct Loki Software and all the development team.

## Build instructions

In order to build the project, run from the main folder:

c:\yourfolder\ > gcc main.c ball.h ball.c player.h player.c text.h text.c utils.h utils.c -L./SDL2/lib -I./SDL2/include/ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -o./bin/Debug/pong.exe -w -Wextra -Wfatal-errors

On Linux and Mac OS, you can use the same command, just remove "-L./SDL2/lib -I./SDL2/include/ -lmingw32", you normally don't need this.
On Linux you need to install libSDL2-dev, libSDL2_image-dev, libSDL2_mixer-dev packages.
On Mac you also need the development packages; you can install them with Homebrew or Mac Ports.
If you install them from the SDL2 website you need the -L/path/ and -I/path/ directives for gcc, pointing to the correct subfolders in the Framework folder.

## Additional information and license
If you need help, send me a message: framin2 at gmail.com.

I got the sounds and font for free. I added the font licence file in the fonts folder but I cannot find the audio source anymore. If you recognize it, please, drop me a message so that I can give proper attribution. 

I made the sprites myself with Microsoft Paint. They are a perfect example of programmer art :p
Feel free to reuse them at your will.

My code is provided with MIT license, use it at your will.