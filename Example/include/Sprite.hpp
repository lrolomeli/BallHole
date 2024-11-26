#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameDefs.h"
#include "GameObject.hpp"

class Sprite{
    public:
        Sprite(GameObject * gobj, SDL_Renderer* renderer, int xpos, int ypos, uint8_t color);
        ~Sprite();
        void updatePositionX(int x);
        void updatePositionY(int y);
        void updatePosition(int x, int y);
        void render(SDL_Renderer* renderer);

    private:
        SDL_Rect src, dst;
        SDL_Texture* texture;
        Color c;

};