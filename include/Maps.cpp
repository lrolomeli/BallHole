#include "Maps.h"
#include "Physics.h"

void initMap(stGameObject * board)
{

    for(int i=0; i<BOARDBOXES; i++)
    {
        board[i].type = None;
        board[i].position = OUT_OF_RANGE;
        board[i].color = {BLACK};
    }

}