#include "Colors.h"
#include "GameObject.h"

#define DONE 1
#define NOT_DONE 0

#define ElementsL1 6
#define ElementsL2 15
#define ElementsL3 9
#define ElementsL4 15
#define ElementsL5 18
#define ElementsL6 21

#define BallsL1 1
#define BallsL2 3


#define L1_E    Ball, RED, (10),\
                Hole, RED, (99),\
                Spike, WHITE, (55),\
                Block, WHITE, (23),\
                Block, WHITE, (74),\
                Block, WHITE, (96)

#define L2_E    Ball, RED, (66),\
                Hole, RED, (37),\
                Ball, BLUE, (21),\
                Hole, BLUE, (14),\
                Ball, GREEN, (62),\
                Hole, GREEN, (46),\
                Spike, WHITE, (13),\
                Spike, WHITE, (24),\
                Spike, WHITE, (55),\
                Spike, WHITE, (85),\
                Block, WHITE, (41),\
                Block, WHITE, (43),\
                Block, WHITE, (64),\
                Block, WHITE, (78),\
                Block, WHITE, (94)



enum LEVEL{
    LEVEL1 = 0,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LEVEL6,
};


void initMap(stGameObject * board);
