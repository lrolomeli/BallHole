#include "Core.hpp"
#include "Game.hpp"
#include <iostream>

Game::Game(const char* title){
    gameCore = new Core();
    if(init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENSIZE, SCREENSIZE))
    {
        std::cout << "Init Succesfull." << std::endl;
    }
}

Game::~Game(){}

bool Game::init(const char* title, int xpos, int ypos, int width, int height){

    if(0 != SDL_Init(SDL_INIT_EVERYTHING)) return false;
    if(0 == IMG_Init(IMG_INIT_PNG)) return false;

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if(nullptr == window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(nullptr == renderer) return false;

    return gameCore->start(renderer);
}

void Game::handleEvents(){
    SDL_Event event;    
    SDL_WaitEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            gameCore->stop();
            break;
        case SDL_KEYDOWN:
            if(gameCore->objInMotion()) break; // if an obj is in motion dont accept keys to move
            if(!gameCore->ballSelected()) break; // if not ball is selected dont accept
            if(event.key.keysym.scancode >= SDL_SCANCODE_RIGHT && event.key.keysym.scancode <= SDL_SCANCODE_UP) {
                gameCore->direction((uint8_t)(event.key.keysym.scancode - SDL_SCANCODE_RIGHT));
            }                      
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(gameCore->objInMotion()) break;
            gameCore->getClickPos(event.button.x, event.button.y);
            break;
        default:
            break;
    }

}

void Game::update(){
    gameCore->update(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::render(){

    gameCore->drawBoard(renderer);
    gameCore->drawSprites(renderer);
    SDL_RenderPresent(renderer);
    
    if(gameCore->objInMotion()) {
        gameCore->updateMovingSprite();
        render();
    }        

}

bool Game::running(){
    return gameCore->isRunning();
}