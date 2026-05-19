#include "display.h"
#include "text.h"
#include <SDL3/SDL.h>
#include <stdbool.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // Create display
    Display* disp = DISP_newDisplay("Text Module Test", 800, 600);
    if (!disp || !disp->window || !disp->renderer) {
        SDL_Log("Failed to create display");
        SDL_Quit();
        return 1;
    }

    // Initialize text renderer
    TextRenderer tR;
    TXT_initTextRenderer(&tR, disp);
    if (!tR.chrSheet) {
        SDL_Log("Failed to load font texture");
        DISP_freeDisplay(disp);
        SDL_Quit();
        return 1;
    }

    // Main loop
    SDL_Event e;
    bool running = true;
    
    while (running) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Clear screen
        DISP_clearDisplay(disp);

        // Write text
        SDL_Rect pos = {100, 100, tR.chrW, tR.chrH};
        TXT_writeTxt(&tR, &pos, "Hello World!", disp);
        
        pos.x = 100;
        pos.y = 150;
        TXT_writeTxt(&tR, &pos, "CPongC Text Module Test", disp);
        
        pos.x = 100;
        pos.y = 200;
        TXT_writeTxt(&tR, &pos, "1234567890", disp);

        // Update display
        DISP_update(disp);
    }

    // Cleanup
    TXT_freeTextRenderer(&tR);
    DISP_freeDisplay(disp);
    SDL_Quit();
    
    return 0;
}
