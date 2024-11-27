#include "GameObject.hpp"


GameObject::GameObject(const char* filepath, SDL_Renderer* renderer) {
    texture = IMG_LoadTexture(renderer, filepath);
    if(NULL != texture) {
        (void) SDL_QueryTexture(texture, nullptr ,nullptr , &width, &height);
    }
}

GameObject::~GameObject() {}

SDL_Texture* GameObject::GetTexture() {
    return texture;
}

int GameObject::getWidth(){
    return width;
}
int GameObject::getHeight(){
    return height;
}
