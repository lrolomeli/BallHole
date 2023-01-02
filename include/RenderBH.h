#ifndef RENDERBH_H
#define RENDERBH_H

#include "GameObject.h"


#define SCREENSIZE 500

class RenderBH
{
public:

    float xscr, yscr;
    RenderBH();
    void motion(float speed, float distance, uint8_t dir);
    void eraseBall(stDisplayPosition * pos, float objSize);
    void loadBoard(stGameObject * obj, stDisplayPosition * pos, float objSize);
    void reDrawBall(stGameObject * obj, stDisplayPosition * pos, float objSize);
    void gameOver();
    bool isWindowOpen();
    bool waitEvent();
    void display();
    sf::Event getEvent();
    void closeWindow();

private:
    sf::RenderWindow *window;
    sf::Event event;
    sf::Texture ball, hole, spike, block, erase;
    sf::Font krunch;
    sf::Text gameMsg;
    sf::Sprite sprite;
    void loadTextures();
    
};

#endif /*RENDERBH_H*/
