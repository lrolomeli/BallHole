#include "Sprite.hpp"
// necesitamos un game object tal que este pertenece a una imagen
// en concreto y se conocen sus dimensiones
Sprite::Sprite(GameObject * gobj, SDL_Renderer* renderer, int xpos, int ypos, uint8_t color) {
    src.x = 0;
    src.y = 0;
    src.w = gobj->getWidth();
    src.h = gobj->getHeight();

    dst.x = xpos;
    dst.y = ypos;
    dst.w = boardsize/10;
    dst.h = boardsize/10;

    texture = gobj->GetTexture();
    
    if(NoColor > color) {
        c = getColor((Colors) color);
    }
    else {
        c = nullptr;
    }
    
}

Sprite::~Sprite() {}


void Sprite::updatePosition(int x, int y) {
    dst.x = x;
    dst.y = y;
}

void Sprite::updatePositionX(int x) {
    dst.x = x;
}

void Sprite::updatePositionY(int y) {
    dst.y = y;
}

void Sprite::render(SDL_Renderer* renderer) {
    if(nullptr != c) SDL_SetTextureColorMod(texture, c->r, c->g, c->b);
    SDL_RenderCopy(renderer, texture, &src, &dst);
}