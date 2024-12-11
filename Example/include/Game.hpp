#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Core.hpp"

class Game{
    public:
        Game(const char* title);
        ~Game();

        bool init(const char* title, int xpos, int ypos, int width, int height);
        void handleEvents();
        void update();
        void clean();
        void render();
        bool running();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Core* gameCore;
};