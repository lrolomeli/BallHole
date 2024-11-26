#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GFXMath.hpp"

class Entity{
    public:
        Entity(Vector2f p_v, SDL_Texture* p_tex);
        Vector2f& getPosition();
        void init();
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
    private:
        Vector2f v;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};