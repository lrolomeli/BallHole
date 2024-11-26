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

    if(NOCOLOR == color) {
        texture = gobj->GetTexture();
    }
    else {
        Color* c = getColor((Colors) color);
        texture = gobj->createColoredTexture(renderer, c);
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
    SDL_RenderCopy(renderer, texture, &src, &dst);
}