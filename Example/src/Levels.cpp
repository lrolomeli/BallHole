# include "Levels.h"

const uint8_t lv1c[] = {LV1_C};
const uint8_t lv2c[] = {LV2_C};

const GElement gelv1[] = {{0,RED,BALL},
{1,RED,HOLE},
{2,NOCOLOR,SPIKE},
{3,NOCOLOR,BLOCK},
{4,NOCOLOR,BLOCK},
{5,NOCOLOR,BLOCK}
};

const GElement gelv2[] = {{0,RED,BALL},
{1,RED,HOLE},
{2,BLUE,BALL},
{3,BLUE,HOLE},
{4,GREEN,BALL},
{5,GREEN,HOLE},
{6,NOCOLOR,SPIKE},
{7,NOCOLOR,SPIKE},
{8,NOCOLOR,SPIKE},
{9,NOCOLOR,SPIKE},
{10,NOCOLOR,BLOCK},
{11,NOCOLOR,BLOCK},
{12,NOCOLOR,BLOCK},
{13,NOCOLOR,BLOCK},
{14,NOCOLOR,BLOCK}
};

Level lv1 = {lv1c, gelv1, sizeof(lv1c)};
Level lv2 = {lv2c, gelv2, sizeof(lv2c)};

const Level levels[] = {lv1, lv2};


const Level* getLevel(uint8_t level) {
    return &levels[level];
}