#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameDefs.h"
#include "GameObject.hpp"

class Sprite{
    public:
        Sprite(GameObject * gobj, SDL_Renderer* renderer, int xpos, int ypos, uint8_t color);
        ~Sprite();
        void moveX(bool di);
        void moveY(bool di);
        void updatePosition(int x, int y);
        void render(SDL_Renderer* renderer);
        int getX();
        int getY();
        void setVisibility(bool renderizable);

    private:
        bool renderizable;
        SDL_Rect src, dst;
        SDL_Texture* texture;
        Color* c;

};