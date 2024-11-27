#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[]) {
    Game* game = new Game("HB v1.0");
    //Game game("HB v1.0");
    game->loadLevel(0);

    while(game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}