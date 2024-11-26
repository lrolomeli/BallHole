#include "Entity.hpp"

Entity::Entity(Vector2f p_v, SDL_Texture* p_tex) : v(p_v) ,tex(p_tex)  {
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}

Vector2f& Entity::getPosition(){
    return v;
}

SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}