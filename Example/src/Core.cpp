#include "Core.hpp"
#include <iostream>

Core::Core(){
    motion = false;
    act_gElem =  nullptr;
    pos_act_gE = 255;
    click = false;
    moving = false;
    result = CONTINUE;
}

bool Core::start(SDL_Renderer* renderer) {
    const char* obj_res[4] = {"res/gfx/ball.png","res/gfx/hole.png","res/gfx/block.png","res/gfx/spike.png"};
    board = IMG_LoadTexture(renderer, "res/gfx/1010board.png");
    if(nullptr == board) return false;

    for(uint8_t i=0; i<4; i++) {
        e_gObj[i] = new GameObject(obj_res[i], renderer);
        if(nullptr == e_gObj[i]) return false;
    }

    loadLevel(1);
    loadSprites(renderer);

    running = true;
    return true;
}

bool Core::isRunning() {
    return running;
}

void Core::stop() {
    running = false;
}

bool Core::objInMotion() {
    return moving;
}

bool Core::ballSelected() {
    if(nullptr != act_gElem) return true;
    else return false;
}

void Core::getSpritePosition(uint8_t pos, int& x, int& y) {
    x = (pos % 10) * cellsize;
    y = (pos / 10) * cellsize;
}

void Core::loadSprites(SDL_Renderer* renderer) {
    int x,y;
    s_elem = std::vector<Sprite*>(lv->e_size);
    // Cargar los objetos y asociarlos con su Id
    for(uint8_t i=0; i<lv->e_size; i++) {
        getSpritePosition(lv->coord[i], x, y);
        GameObject* gobj = e_gObj[lv->e[i].type];
        s_elem[i] = new Sprite(gobj, renderer, x, y, lv->e[i].color);
    }
}

void Core::loadLevel(uint8_t level) {
    lv = getLevel(level);

    for(uint8_t i=0; i<lv->e_size; i++) {
        gameMapElem[lv->coord[i]] = lv->e[i];
    }
}

void Core::getClickPos(Sint32 x, Sint32 y) {

	x = (x*10) / boardsize;
	pos.x = (uint8_t) x;
	
	y = (y*10) / boardsize;
	pos.y = (uint8_t) y;
	
	pos_act_gE = pos.x + (pos.y * 10);
    
    click = true;
}

void Core::direction(uint8_t m) {
    if(m < 2) ax = xAxis; // 0 izquierda, 1 derecha, motion x axis
    else ax = yAxis; // 2 arriba, 3 abajo, motion y axis
    if(m % 2) di = false; // numero par reduce la posicion izq, arriba
    else di = true; // numero impar aumenta la posicion derecha, abajo
    motion = true;
}

void Core::searchBall() {
    auto e = gameMapElem.find(pos_act_gE);
    if(e == gameMapElem.end()) return;
    if(BALL == e->second.type) act_gElem = &e->second;
}

void Core::getCollision(uint8_t pos) {
    // std::cout << std::to_string(pos) << std::endl;

    auto e = gameMapElem.find(pos);
    if(e == gameMapElem.end()) result = CONTINUE; // continue moving.
    else if(SPIKE == e->second.type) result = GAMEOVER; // stop motion, reset the game. (let animation flow)
    else if(HOLE == e->second.type && e->second.color == act_gElem->color) result = SCORE; // stop motion, remove ball, increment score.
    else result = STOP;

    // std::cout << std::to_string(result) << std::endl;
}

void Core::updateGEPosition() {
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

void Core::evaluateResult() {
    if(STOP == result || CONTINUE == result) {
        updateGEPosition();
    }
    else if(SCORE == result) {
        // cual elemento estamos eliminando se supone que el actual
        std::cout << std::to_string(pos_act_gE) << std::endl;
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

void Core::travel(int8_t dist) {
    int8_t i;
    moves++;// incrementar el numero de movimientos

    if(dist > 0) {
        i = 1;
    }
    else {
        i = -1;
        dist *= -1;
    }
    
    while(CONTINUE == result && dist > 0) {
        if(ax) pos.x += i;
        else pos.y += i;
        getCollision((pos.y*10) + pos.x);
        if(result == STOP) { // evita que dos objetos ocupen un mismo sitio
            if(ax) pos.x += i*(-1);
            else pos.y += i*(-1);
        }
        dist--;
    }

    evaluateResult();

    moving = true;
}

void Core::predictMove() {
    int8_t dest, origin, dist;

    if(di) dest = 9;
    else dest = 0;

    if(ax) origin = pos.x;
    else origin = pos.y;

    dist = dest - origin;
    if(dist != 0) travel(dist);
}

void Core::updateMovingSprite() {
    int target;

    if(ax == xAxis) {
        // deten el movimiento cuando la posicion actual del 
        // moving sprite sea igual a la posicion final
        target = pos.x * cellsize;
        // std::cout << std::to_string(s_elem[act_gElem->id]->getX()) << std::endl;
        if(s_elem[act_gElem->id]->getX() == target) moving = false;
        else s_elem[act_gElem->id]->moveX(di);
    }
    else {
        // deten el movimiento cuando la posicion actual del 
        // moving sprite sea igual a la posicion final
        target = pos.y * cellsize;
        // std::cout << std::to_string(s_elem[act_gElem->id]->getY()) << std::endl;
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
            running = false;
        }
        else {

        }
        result = CONTINUE;
    }

}


void Core::update(SDL_Renderer* renderer) {
    if(click) {
        searchBall();
        click = false;
    }
    if(motion) {
        predictMove();
        motion = false;
    }
}

void Core::drawSprites(SDL_Renderer* renderer) {
    for(Sprite* s_e : s_elem) {
        s_e->render(renderer);
    }
}

void Core::drawBoard(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_SetTextureColorMod(board, RGB_DARK_GRAY);
    SDL_RenderCopy(renderer, board, NULL, NULL);
}