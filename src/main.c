//
// Created by clement on 15/10/2025.
//

#include <SDL3/SDL_main.h>

#include "util.h"
#include "game.h"

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        GOL_LOG_ERROR("SDL Could not init Video");
        return 1;
    }

    Window *window = GOL_CreateWindow();
    if (!window) {
        GOL_LOG_ERROR("Could not create window");
        SDL_Quit();
        return 1;
    }

    Game *game = GOL_CreateGame(window);
    GOL_GameStart(game);

    GOL_DestroyGame(game);
    GOL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
