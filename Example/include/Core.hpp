#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Levels.h"

class Core{
    public:
        Core();
        ~Core();

        bool start(SDL_Renderer* renderer);
        bool isRunning();
        void stop();
        void loadLevel(uint8_t level);
        void direction(uint8_t m);
        void update(SDL_Renderer* renderer);
        bool objInMotion();
        bool ballSelected();
        void getClickPos(Sint32 x, Sint32 y);
        void drawBoard(SDL_Renderer* renderer);
        void drawSprites(SDL_Renderer* renderer);
        void updateMovingSprite();

    private:
        bool running, moving, click, ax, di, motion;
        uint8_t pos_act_gE, moves, result;
        Position pos, old_pos;
        const Level* lv;
        GElement* act_gElem;
        SDL_Texture* board;
        GameObject* e_gObj[4];
        std::unordered_map<uint8_t, GElement> gameMapElem;
        std::vector<Sprite*> s_elem;
        void loadSprites(SDL_Renderer* renderer);
        void getSpritePosition(uint8_t pos, int& x, int& y);
        void searchBall();
        void predictMove();
        void getCollision(uint8_t pos);
        void travel(int8_t dist);
        void evaluateResult();
        void updateGEPosition();
};