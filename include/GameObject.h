#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Colors.h"

#define BOXES 10
#define BOARDBOX_ROW 10
#define BOARDBOX_COL 10
#define BOARDBOXES (BOARDBOX_ROW * BOARDBOX_COL)

typedef unsigned char uint8_t;

enum enGameObjType{ None, Ball, Hole, Block, Spike };

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

}stGameObjColor;

typedef struct
{
    float x;
    float y;

}stDisplayPosition;


typedef struct
{
    enGameObjType type;
    stGameObjColor color;
    uint8_t position;

}stGameObject;

typedef struct
{
    uint8_t ballEvent;
    uint8_t lastPosition;

}stBallEvent;

typedef struct
{
    const stGameObject * elements;
    uint8_t size;
    uint8_t goals : 4;

}stLevel;

typedef struct
{
    float w;
    float h;
}stScreenBoardSize;

typedef struct
{
    float x;
    float y;
}stMousePosition;

class GameObject
{
public:
    
    GameObject();
    GameObject(uint8_t position, enGameObjType type);
    ~GameObject();
    void setPosition(uint8_t position);
    uint8_t * getPosition();
    enGameObjType getObjType();

private:
    uint8_t position;
    enGameObjType type;

};