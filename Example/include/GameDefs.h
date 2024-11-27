#pragma once

#include <cstdint>

#define boardsize 400

#define BALL 0
#define HOLE 1
#define BLOCK 2
#define SPIKE 3

#define RGB_BLACK   0  , 0  , 0  
#define RGB_WHITE   255, 255, 255
#define RGB_RED     255, 0  , 0  
#define RGB_GREEN   0  , 255, 0  
#define RGB_BLUE    0  , 0  , 255
#define RGB_GRAY    127, 127, 127

#define BLACK   (0U)
#define WHITE   (1U)
#define RED     (2U)
#define GREEN   (3U)
#define BLUE    (4U)
#define GRAY    (5U)
#define NOCOLOR (6U)

enum Colors {
    Black = 0, White = 1, Red = 2, Green = 3, Blue = 4, Gray = 5, NoColor = 6
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct GElement {
    uint8_t id:7;
    uint8_t color:3;
    uint8_t type:2;
};

Color* getColor(Colors c);
