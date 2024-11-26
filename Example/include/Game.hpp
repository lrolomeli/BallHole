#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Levels.h"

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
        void loadLevel(uint8_t level);
    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* board;
        GameObject* e_gObj[4];
        std::unordered_map<uint8_t, GElement> gameMapElem;
        std::vector<Sprite*> s_elem;
        void loadSprites(const Level* lv);
        void getSpritePosition(uint8_t pos, int& x, int& y);
};