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

// Helper function to create a texture with a fixed color modulation
SDL_Texture* GameObject::createColoredTexture(SDL_Renderer* renderer, Color* color) {
    // Obtener dimensiones de la textura base
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    // Crear una nueva textura como render target
    SDL_Texture* coloredTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!coloredTexture) {
        return NULL;
    }
    // Configurar la nueva textura como objetivo de renderizado
    SDL_SetRenderTarget(renderer, coloredTexture);

    // Modificar los colores de la textura base
    SDL_SetTextureColorMod(texture, color->r, color->g, color->b);

    // Copiar la textura base modulada sobre el render target
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Restaurar el render target a la pantalla
    SDL_SetRenderTarget(renderer, NULL);

    return coloredTexture;
}

int GameObject::getWidth(){
    return width;
}
int GameObject::getHeight(){
    return height;
}
