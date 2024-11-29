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

    renderizable = true;
    
}

Sprite::~Sprite() {}


void Sprite::updatePosition(int x, int y) {
    dst.x = x;
    dst.y = y;
}

void Sprite::moveX(bool di) {
    if(di) dst.x += speed;
    else dst.x -= speed;
}

void Sprite::moveY(bool di) {
    if(di) dst.y += speed;
    else dst.y -= speed;
}

int Sprite::getX() {
    return dst.x;
}

int Sprite::getY() {
    return dst.y;
}

void Sprite::setVisibility(bool renderizable) {
    this->renderizable = renderizable;
}

void Sprite::render(SDL_Renderer* renderer) {
    if(nullptr != c) SDL_SetTextureColorMod(texture, c->r, c->g, c->b);
    if(renderizable) SDL_RenderCopy(renderer, texture, &src, &dst);
}