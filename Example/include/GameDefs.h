#pragma once

#include <cstdint>

#define boardsize (400U)
#define ColRow (10U)
#define cellsize ((boardsize)/(ColRow))
#define speed 10 // Pixeles per frame // 240 px per second // a 60 fps
#define SCREENSIZE 400

#define xAxis true
#define yAxis false

#define BALL 0
#define HOLE 1
#define BLOCK 2
#define SPIKE 3

#define RGB_BLACK       0  , 0  , 0  
#define RGB_WHITE       255, 255, 255
#define RGB_RED         255, 0  , 0  
#define RGB_GREEN       0  , 255, 0  
#define RGB_BLUE        0  , 0  , 255
#define RGB_GRAY        127, 127, 127
#define RGB_DARK_GRAY   36 , 36 , 36

#define BLACK       (0U)
#define WHITE       (1U)
#define RED         (2U)
#define GREEN       (3U)
#define BLUE        (4U)
#define GRAY        (5U)
#define DARK_GRAY   (6U)
#define NOCOLOR     (15U)

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3
#define FREEZED 4

#define CONTINUE 0
#define STOP 1
#define SCORE 2
#define GAMEOVER 3

enum Colors {
    Black = 0, White = 1, Red = 2, Green = 3, Blue = 4, Gray = 5, Dark_Gray = 6, NoColor = 15
};

enum Direction {
    Right = 0, Left = 1, Up = 2, Down = 3, Freezed = 4
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct GElement {
    uint8_t id:7;
    uint8_t color:4;
    uint8_t type:2;
};

struct Position{
    uint8_t x:4;
    uint8_t y:4;
};

Color* getColor(Colors c);

