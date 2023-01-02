#include "Event.h"
#include "Physics.h"

void pickingBall(float mouse_x, float mouse_y, float scrdim, stGameObject * board, stGameObject * selectedBall)
{
    uint8_t box;

    box = getClickBox(mouse_x, mouse_y, scrdim);

    if (isThereABall(board[box].type))
    {
        selectBall(board, selectedBall, box);
    }
    else
    {
        unselectBall(selectedBall);
    }

}

void displacement(uint8_t direction, stGameObject * selectedBall, stGameObject * board, stBallEvent *ev)
{
    /* calculate next position based on tiny map */
    /* we will have a selected object based on event */
    /* from there once the arrow keys are pressed */
    /* we can obtain the position of the object */
    /* so once we have the position we passed it to the tiny map */
    /* to compare */
    // check for selected ball
    if (Ball == selectedBall->type)
    {
        ev->lastPosition = selectedBall->position;
        do
        {
            ev->ballEvent = calculateNewPosition(selectedBall, direction, board);
        } while (VALID_POSITION == ev->ballEvent);

        if (ev->lastPosition == selectedBall->position)
        {
            // erase the ball from last position and redraw it into to the current position
            ev = nullptr;
        }

    }

}


uint8_t getClickBox(float mouse_x, float mouse_y, float scrdim)
{
    uint8_t x_box, y_box;

    x_box = (uint8_t)(mouse_x / (scrdim / ((float)BOARDBOX_ROW)));
    y_box = (uint8_t)(mouse_y / (scrdim / ((float)BOARDBOX_COL)));

    // obtain the coordinates of the balls in the game
    return (y_box * 10) + x_box;
}


bool isThereABall(uint8_t objType)
{
    if (Ball == objType)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void selectBall(stGameObject * board, stGameObject * selectedBall, uint8_t box)
{
        selectedBall->color = board[box].color;
        selectedBall->position = board[box].position;
        selectedBall->type = board[box].type;

}

void unselectBall(stGameObject * selectedBall)
{
    selectedBall->color = { BLACK };
    selectedBall->position = OUT_OF_RANGE;
    selectedBall->type = None;
}
