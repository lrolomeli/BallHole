#pragma once

#include "GameDefs.h"

#define LV1_C    10, 99, 55, 23, 74, 96
#define LV2_C    66, 37, 21, 14, 62, 46, 13, 24, 55, 85, 41, 43, 64, 78, 94

struct Level{
    const uint8_t* coord;
    const GElement* e;
    const uint8_t e_size;
};

const Level* getLevel(uint8_t level);