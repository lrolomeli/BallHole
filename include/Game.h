
#include "GameObject.h"
#include "RenderBH.h"

class Game
{
public:
    Game();
    Game(RenderBH * render);
    void startGame();

private:
    RenderBH *render;
    stScreenBoardSize screenboard;
    stMousePosition mouseClick;
    stGameObject board[BOARDBOXES];
    stGameObject selectedBall;
    stLevel currentLevel;
    uint8_t scoreLevel;
    stBallEvent ballEv;
    float objSize;
    void gameLoop();
    void loadBoard();
    void loadElements(uint8_t element);
    void refreshBall(stBallEvent * ball);
    void eraseBall(uint8_t position);
    void reDrawBall();
    void moveBall(stBallEvent * ev, uint8_t dir);
    void ballMotion(stDisplayPosition * pos);

};