#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameDefs.h"

class GameObject{
    public:
        GameObject(const char* filepath, SDL_Renderer* renderer);
        ~GameObject();
        int getWidth();
        int getHeight();
        SDL_Texture* GetTexture();
        SDL_Texture* createColoredTexture(SDL_Renderer* renderer, Color* color);

    private:
        SDL_Texture* texture;
        int width, height;

};