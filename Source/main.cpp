#include <iostream>
#include <SDL.h>
#include <ctime>
#include "game.h"

int main(int argc, char* argv[]){
    srand(time(nullptr));
    Game *game = new Game();

    game->initialize();

    while (true) {
        game->update();

        game->render();

        game->events();

        SDL_Delay(16);
    }


    delete game;

    return 0;
}
