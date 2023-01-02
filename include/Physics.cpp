#include "Physics.h"

int travelDistance(stScreenBoardSize * screenboard, uint8_t initial, uint8_t final){
    
    int result;
    float distance;

    result = final - initial;
    // abs(final - initial) > 9 go up or down (result / 10) x screen / 10 
    // else go left or right  result x screen / 10

    if(result>0)
    {
        //abajo o derecha
        if(result>9)
        {
            //abajo
            distance = (result / 10) * (screenboard->h / BOXES);
        }
        else
        {
            //derecha
            distance = result * (screenboard->w / BOXES);
        }
    }
    else
    {
        //arriba o izquierda
        if((-result)>9)
        {
            //arriba
            distance = ((-result) / 10) * (screenboard->h / BOXES);
        }
        else
        {
            //izquierda
            distance = (-result) * (screenboard->w / BOXES);
        }
    }

    return (int) (distance / SPEED);

}


void getDisplayPosition(stDisplayPosition * dp, stScreenBoardSize * screenboard, uint8_t position){
    
    uint8_t xint, yint;

    yint = position / 10;
    xint = position - (yint * 10);
    dp->x = (float)xint * (screenboard->w / BOXES);
    dp->y = (float)yint * (screenboard->h / BOXES);

}

bool matches(stGameObjColor color1, stGameObjColor color2)
{
    return (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b);
}

uint8_t validateNextPosition(uint8_t position, stGameObjColor colorball, stGameObject * board)
{
    switch (board[position].type)
    {
    case None:
        return VALID_POSITION;
        break;

    case Hole:
        if (matches(board[position].color, colorball))
            // We have scored a goal.
            return GOAL;
        break;

    case Spike:
        // Game Is Over
        return GAME_OVER;
        break;

    default:
        return INVALID_POSITION;
        break;
    }

    return INVALID_POSITION;

}


/* Esta funcion hay que dividirla por que hace demasiados calculos. */
/* debe devolver si el movimiento */
uint8_t calculateNewPosition(stGameObject *gameObj, uint8_t direction, stGameObject * board)
{
    uint8_t nextPosition;
    uint8_t result = OUT_OF_RANGE;
    nextPosition = gameObj->position;


    /* Validamos que no salgamos del tablero */
    /* Avanzando 1 celda a la vez */
    switch (direction)
    {
    case LEFT:
        if (( (gameObj->position) % 10 ) > 0){
            nextPosition--;
        }
        else
        {
            nextPosition = OUT_OF_RANGE;
        }
        break;
    case RIGHT:
        if (( (gameObj->position) % 10 ) < 9){
            nextPosition++;
        }
        else
        {
            nextPosition = OUT_OF_RANGE;
        }
        break;
    case DOWN:
        if ((gameObj->position) < 90){
            nextPosition += 10;
        }
        else
        {
            nextPosition = OUT_OF_RANGE;
        }
        break;
    case UP:
        if ((gameObj->position) > 9){
            nextPosition -= 10;
        }
        else
        {
            nextPosition = OUT_OF_RANGE;
        }
        break;
    default:
        nextPosition = OUT_OF_RANGE;
        break;
    }

    if (nextPosition != (gameObj->position) && nextPosition < OUT_OF_RANGE)
    {
        result = validateNextPosition(nextPosition, gameObj->color, &board[0]);

        switch (result)
        {
        case VALID_POSITION:
            gameObj->position = nextPosition;
            break;

        case INVALID_POSITION:
            result = OUT_OF_RANGE;
            break;

        case GOAL:
            result = GOAL;
            break;

        case GAME_OVER:
            result = GAME_OVER;
            break;

        default:
            result = OUT_OF_RANGE;
            break;
        }

    }

    return result;

}