#ifndef PHYSICS_H
#define PHYSICS_H

#include "GameObject.h"

#define SPEED 5

enum dir{
    LEFT = 1,
    RIGHT,
    UP,
    DOWN
};

enum enScenarios{
    OUT_OF_RANGE = 100,
    VALID_POSITION,
    INVALID_POSITION,
    GOAL,
    GAME_OVER = 255
};


bool matches(stGameObjColor color1, stGameObjColor color2);
uint8_t validateNextPosition(uint8_t position, stGameObjColor colorball, stGameObject * board);
uint8_t calculateNewPosition(stGameObject *gameObj, uint8_t direction, stGameObject * board);
void getDisplayPosition(stDisplayPosition * dp, stScreenBoardSize * screenboard, uint8_t position);
int travelDistance(stScreenBoardSize * screenboard, uint8_t initial, uint8_t final);

#endif