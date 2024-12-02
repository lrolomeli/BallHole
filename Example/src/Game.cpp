#include "Game.hpp"
#include "Levels.h"
#include <iostream>

const char* e_paths[4] = {"res/gfx/ball.png","res/gfx/hole.png","res/gfx/block.png","res/gfx/spike.png"};

Game::Game(const char* title){
    if(init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENSIZE, SCREENSIZE))
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
    if(nullptr == window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(nullptr == renderer) return false;

    board = IMG_LoadTexture(renderer, "res/gfx/1010board.png");
    if(nullptr == board) return false;

    for(uint8_t i=0; i<4; i++) {
        e_gObj[i] = new GameObject(e_paths[i], renderer);
        if(nullptr == e_gObj[i]) return false;
    }

    motion = false;
    act_gElem =  nullptr;
    pos_act_gE = 255;
    click = false;
    moving = false;
    result = CONTINUE;

    return true;
}

void Game::getSpritePosition(uint8_t pos, int& x, int& y) {
    x = (pos % 10) * cellsize;
    y = (pos / 10) * cellsize;
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

uint8_t Game::getClickPos(Sint32 x, Sint32 y) {
	
	x = (x*10) / boardsize;
	pos.x = (uint8_t) x;
	
	y = (y*10) / boardsize;
	pos.y = (uint8_t) y;
	
	return pos.x + (pos.y * 10);
}

void Game::direction(uint8_t m) {
    if(m < 2) ax = xAxis;
    else ax = yAxis;
    if(m % 2) di = false;
    else di = true;
}

void Game::handleEvents(){
    SDL_Event event;    
    SDL_WaitEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(moving) break;
            if(nullptr == act_gElem) break;
            if(event.key.keysym.scancode >= SDL_SCANCODE_RIGHT && event.key.keysym.scancode <= SDL_SCANCODE_UP) {
                direction((uint8_t)(event.key.keysym.scancode - SDL_SCANCODE_RIGHT));
                motion = true;
            }                      
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(moving) break;
            pos_act_gE = getClickPos(event.button.x, event.button.y);
            click = true;
            break;
        default:
            break;
    }

}

void Game::searchBall(uint8_t pos) {
    auto e = gameMapElem.find(pos);
    if(e == gameMapElem.end()) return;
    if(BALL == e->second.type) act_gElem = &e->second;
}

void Game::getCollision(uint8_t pos) {

    auto e = gameMapElem.find(pos);
    if(e == gameMapElem.end()) result = CONTINUE; // continue moving.
    else if(SPIKE == e->second.type) result = GAMEOVER; // stop motion, reset the game. (let animation flow)
    else if(HOLE == e->second.type && e->second.color == act_gElem->color) result = SCORE; // stop motion, remove ball, increment score.
    else result = STOP;
}

void Game::updateGEPosition() {
    uint8_t new_pos;
    GElement temp;

    temp.id = act_gElem->id;
    temp.color = act_gElem->color;
    temp.type = act_gElem->type;
    // eliminar el objeto en movimiento
    gameMapElem.erase(pos_act_gE);
    new_pos = (pos.y*10) + pos.x;
    gameMapElem[new_pos] = temp;
    pos_act_gE = new_pos;
}

void Game::evaluateResult() {
    if(STOP == result) {
        updateGEPosition();
    }
    else if(SCORE == result) {
        // cual elemento estamos eliminando se supone que el actual
        gameMapElem.erase(pos_act_gE);
        pos_act_gE = 255;
    }
    else if(GAMEOVER == result) {
        gameMapElem.erase(pos_act_gE);
        pos_act_gE = 255;
    }
    else {
        
    }
}

void Game::travel(int8_t dist) {
    int8_t i;

    // incrementar el numero de movimientos
    moves++;

    if(dist > 0) {
        i = 1;
    }
    else {
        i = -1;
        dist *= -1;
    }
    
    while(CONTINUE == result) {
        if(ax) pos.x += i;
        else pos.y += i;
        getCollision((pos.y*10) + pos.x);
        if(result == STOP) { // evita que dos objetos ocupen un mismo sitio
            if(ax) pos.x += i*(-1);
            else pos.y += i*(-1);
        }
        dist--;
        if(0 == dist) result = STOP;
    }

    evaluateResult();

    moving = true;
}

void Game::predictMove() {
    int8_t dest, origin, dist;

    if(di) dest = 9;
    else dest = 0;

    if(ax) origin = pos.x;
    else origin = pos.y;

    dist = dest - origin;
    if(dist != 0) travel(dist);
}

void Game::updateMovingSprite() {
    int target;

    if(ax == xAxis) {
        // deten el movimiento cuando la posicion actual del 
        // moving sprite sea igual a la posicion final
        target = pos.x * cellsize;
        std::cout << std::to_string(s_elem[act_gElem->id]->getX()) << std::endl;
        if(s_elem[act_gElem->id]->getX() == target) moving = false;
        else s_elem[act_gElem->id]->moveX(di);
    }
    else {
        // deten el movimiento cuando la posicion actual del 
        // moving sprite sea igual a la posicion final
        target = pos.y * cellsize;
        std::cout << std::to_string(s_elem[act_gElem->id]->getY()) << std::endl;
        if(s_elem[act_gElem->id]->getY() == target) moving = false;
        else s_elem[act_gElem->id]->moveY(di);
    }

    if (!moving) {
        // llego a la posicion final el objeto
        // si fue un score hay que eliminar el objeto
        if(result == SCORE) {
            // como hacer que el elemento ya no se renderizable sin eliminarlo
            s_elem[act_gElem->id]->setVisibility(false);
            act_gElem = nullptr; // evita que se vuelva a mover
        } 
        else if(result == GAMEOVER) {
            isRunning = false;
        }
        else {

        }
        result = CONTINUE;
    }

}

void Game::update(){
    if(!moving) {
        if(click) {
            searchBall(pos_act_gE);
            click = false;
        }
        if(motion) {
            predictMove();
            motion = false;
        }
    }
    else {
        updateMovingSprite();
    }
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_SetTextureColorMod(board, RGB_DARK_GRAY);
    SDL_RenderCopy(renderer, board, NULL, NULL);

    for(Sprite* s_e : s_elem) {
        s_e->render(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

bool Game::running(){
    return isRunning;
}