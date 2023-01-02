#include "Game.h"
#include "Maps.h"
#include "Event.h"
#include "Physics.h"
#include "RenderBH.h"

static const stGameObject elements_L1[ElementsL1] = { L1_E };
static const stGameObject elements_L2[ElementsL2] = { L2_E };

const stGameObject * pGO_currentLvl[] = { elements_L1, elements_L2 };
const uint8_t u8a_elemLvl[] = { ElementsL1, ElementsL2 };
const uint8_t u8a_ballLvl[] = { BallsL1, BallsL2 };

Game::Game()
{

    render = new RenderBH();
    screenboard.w = render->xscr;
    screenboard.h = render->yscr;
    currentLevel = { pGO_currentLvl[LEVEL2], u8a_elemLvl[LEVEL2], u8a_ballLvl[LEVEL2] };
    objSize = SCREENSIZE / BOXES;
    initMap(&board[0]);
    loadBoard();
}


void Game::startGame(){

    gameLoop();

}

void Game::gameLoop()
{
    while (render->isWindowOpen())
    {
        while (render->waitEvent())
        {
            if (render->getEvent().type == sf::Event::Closed)
            {
                render->closeWindow();
            }
            if (render->getEvent().type == sf::Event::MouseButtonPressed)
            {
                if (render->getEvent().mouseButton.button == sf::Mouse::Left)
                {

                    pickingBall(render->getEvent().mouseButton.x, render->getEvent().mouseButton.y, screenboard.w, &board[0], &selectedBall);

                }
            }
            if (render->getEvent().type == sf::Event::Resized)
            {
                screenboard.w = render->xscr;
                screenboard.h = render->yscr;
            }

            if (render->getEvent().type == sf::Event::KeyPressed)
            {

                if (render->getEvent().key.code == sf::Keyboard::Left)
                {
                    displacement(LEFT, &selectedBall, &board[0], &ballEv);
                    //moveBall(&ballEv, LEFT);
                    refreshBall(&ballEv);
                }
                else if (render->getEvent().key.code == sf::Keyboard::Right)
                {
                    displacement(RIGHT, &selectedBall, &board[0], &ballEv);
                    //moveBall(&ballEv, RIGHT);
                    refreshBall(&ballEv);
                }
                else if (render->getEvent().key.code == sf::Keyboard::Up)
                {
                    displacement(UP, &selectedBall, &board[0], &ballEv);
                    refreshBall(&ballEv);
                    //moveBall(&ballEv, UP);
                }
                else if (render->getEvent().key.code == sf::Keyboard::Down)
                {
                    displacement(DOWN, &selectedBall, &board[0], &ballEv);
                    refreshBall(&ballEv);
                    //moveBall(&ballEv, DOWN);
                }

            }

        }

    }

}

void Game::loadElements(uint8_t element)
{
    stGameObject obj;
    stDisplayPosition pos;

    obj = {currentLevel.elements[element]};

    getDisplayPosition(&pos, &screenboard, obj.position);

    render->loadBoard(&obj, &pos, objSize);

    // place object in map or board
    board[currentLevel.elements[element].position] = currentLevel.elements[element];

}

void Game::loadBoard()
{
    for (uint8_t i = 0; i < currentLevel.size; i++)
    {
        loadElements(i);
    }
    render->display();
}

void Game::eraseBall(uint8_t position)
{
    stDisplayPosition pos;

    getDisplayPosition(&pos, &screenboard, position);

    // remove object from map or board
    board[position] = { None, { BLACK }, 0 };
    render->eraseBall(&pos, objSize);

}

void Game::reDrawBall()
{
    stDisplayPosition pos;

    getDisplayPosition(&pos, &screenboard, selectedBall.position);

    render->reDrawBall(&selectedBall, &pos, objSize);

    // place object in map or board
    board[selectedBall.position] = {selectedBall};

}

void Game::refreshBall(stBallEvent * ev){

        // overwrite black square in old ball position
    if (ev)
    {

        eraseBall(ev->lastPosition);

        if (ev->ballEvent == GOAL)
        {
            selectedBall = { None, { BLACK }, OUT_OF_RANGE };
            scoreLevel++;
            render->display();

        }
        else if (ev->ballEvent == GAME_OVER)
        {
            selectedBall = { None, { BLACK }, OUT_OF_RANGE };
            render->gameOver();
            render->display();

        }
        else
        {
            // draw the ball in new position 
            reDrawBall();
            render->display();
        }

    }

}

void Game::ballMotion(stDisplayPosition * pos)
{
    render->reDrawBall(&selectedBall, pos, objSize);

    // place object in map or board
    board[selectedBall.position] = {selectedBall};

}

void Game::moveBall(stBallEvent * ev, uint8_t dir){

    stDisplayPosition pos;

        // overwrite black square in old ball position
    if (ev)
    {
        int iterations = travelDistance(&screenboard, ev->lastPosition, selectedBall.position);
        getDisplayPosition(&pos, &screenboard, ev->lastPosition);

        switch(dir)
        {
            case LEFT:
                for(int i=0; i<iterations; i++)
                {
                    render->eraseBall(&pos, objSize);
                    render->display();
                    pos.x -= SPEED;
                    render->reDrawBall(&selectedBall, &pos, objSize);
                    render->display();
                }
            break;
            case RIGHT:
                for(int i=0; i<iterations; i++)
                {
                    render->eraseBall(&pos, objSize);
                    render->display();
                    pos.x += SPEED;
                    render->reDrawBall(&selectedBall, &pos, objSize);
                    render->display();
                }
            break;
            case UP:
                for(int i=0; i<iterations; i++)
                {
                    render->eraseBall(&pos, objSize);
                    render->display();
                    pos.y -= SPEED;
                    render->reDrawBall(&selectedBall, &pos, objSize);
                    render->display();
                }
            break;
            case DOWN:
                for(int i=0; i<iterations; i++)
                {
                    render->eraseBall(&pos, objSize);
                    render->display();
                    pos.y += SPEED;
                    render->reDrawBall(&selectedBall, &pos, objSize);
                    render->display();
                }
            break;
        }

        if (ev->ballEvent == GOAL)
        {
            selectedBall = { None, { BLACK }, OUT_OF_RANGE };
            scoreLevel++;
            render->display();

        }
        else if (ev->ballEvent == GAME_OVER)
        {
            selectedBall = { None, { BLACK }, OUT_OF_RANGE };
            render->gameOver();
            render->display();

        }
        else
        {
            // draw the ball in new position 
            reDrawBall();
            render->display();
        }

    }

}