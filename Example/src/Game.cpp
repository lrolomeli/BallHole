#include "Game.hpp"
#include "Levels.h"
#include <iostream>

const char* e_paths[4] = {"res/gfx/ball.png","res/gfx/hole.png","res/gfx/block.png","res/gfx/spike.png"};

Game::Game(const char* title){
    if(init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400))
    {
        std::cout << "Init Succesfull." << std::endl;
        isRunning = true;
    }
}

Game::~Game(){}

bool Game::init(const char* title, int xpos, int ypos, int width, int height){

    if(0 != SDL_Init(SDL_INIT_EVERYTHING)) return false;
    if(0 == IMG_Init(IMG_INIT_PNG)) return false;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(NULL == window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(NULL == renderer) return false;

    board = IMG_LoadTexture(renderer, "res/gfx/1010board.png");
    if(NULL == board) return false;

    for(uint8_t i=0; i<4; i++) {
        e_gObj[i] = new GameObject(e_paths[i], renderer);
        if(NULL == e_gObj[i]) return false;
    }

    return true;
}

void Game::getSpritePosition(uint8_t pos, int& x, int& y) {
    int scale = (boardsize / 10);
    x = (pos % 10) * scale;
    y = (pos / 10) * scale;
}

void Game::loadSprites(const Level* lv) {
    int x,y;
    s_elem = std::vector<Sprite*>(lv->e_size);
    // Cargar los objetos y asociarlos con su Id
    for(uint8_t i=0; i<lv->e_size; i++) {
        getSpritePosition(lv->coord[i], x, y);
        GameObject* gobj = e_gObj[lv->e[i].type];
        s_elem[i] = new Sprite(gobj, renderer, x, y, lv->e[i].color);
    }
}

void Game::loadLevel(uint8_t level) {
    const Level* lv = getLevel(level);

    for(uint8_t i=0; i<lv->e_size; i++) {
        gameMapElem[lv->coord[i]] = lv->e[i];
    }

    loadSprites(lv);
}

void Game::handleEvents(){
    SDL_Event event;
    
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

}

void Game::update(){

}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, board, NULL, NULL);

    for(Sprite* s_e : s_elem) {
        s_e->render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

bool Game::running(){
    return isRunning;
}