#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow{
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char * p_filePath);
        void clear();
        void derender(Entity& p_entity); //Entity rendering
        void hrender(SDL_Texture* p_tex); // hardcoding rendering
        void brender(SDL_Texture* p_tex); // background render texture
        void display();
        void cleanUp();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};