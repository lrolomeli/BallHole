#include "RenderBH.h"
#include "Event.h"

RenderBH::RenderBH()
{
    window = new sf::RenderWindow(sf::VideoMode(SCREENSIZE, SCREENSIZE), "BallHole");
    xscr = SCREENSIZE;
    yscr = SCREENSIZE;
    krunch.loadFromFile("KrunchBold.ttf");
    gameMsg.setFont(krunch);
    window->setFramerateLimit(60);
    window->clear();
    loadTextures();
}


void RenderBH::gameOver(){
    gameMsg.setString("GAME OVER");
    gameMsg.setFillColor(sf::Color::White);
    gameMsg.setCharacterSize(50);
    gameMsg.setPosition(xscr / 2 - gameMsg.getLocalBounds().width / 2, yscr / 2 - gameMsg.getLocalBounds().height);
    window->draw(gameMsg);
}

bool RenderBH::isWindowOpen(){
    return window->isOpen();
}

bool RenderBH::waitEvent(){
    return window->waitEvent(event);
}

sf::Event RenderBH::getEvent()
{
    return event;
}

void RenderBH::display(){
    window->display();
}

void RenderBH::closeWindow(){
    window->close();
}


void RenderBH::motion(float speed, float distance, uint8_t dir){



}

void RenderBH::loadTextures(){
    ball.loadFromFile("ball.png");
    hole.loadFromFile("hole.png");
    spike.loadFromFile("spikei.png");
    block.loadFromFile("block.png");
    erase.loadFromFile("empty.png");
}


void RenderBH::eraseBall(stDisplayPosition * pos, float objSize)
{
    // create object 
    sprite.setTexture(ball);
    sprite.setScale(objSize / (float)(sprite.getTexture()->getSize().x), objSize / (float)(sprite.getTexture()->getSize().y));
    sprite.setColor(sf::Color(BLACK));
    sprite.setPosition(sf::Vector2f(pos->x, pos->y));
    window->draw(sprite);
}

void RenderBH::reDrawBall(stGameObject * obj, stDisplayPosition * pos, float objSize)
{
    // create object 
    sprite.setTexture(ball);
    sprite.setScale(objSize / (float)(sprite.getTexture()->getSize().x), objSize / (float)(sprite.getTexture()->getSize().y));
    sprite.setColor(sf::Color(obj->color.r, obj->color.g, obj->color.b));
    sprite.setPosition(sf::Vector2f(pos->x, pos->y));

    window->draw(sprite);
}
void RenderBH::loadBoard(stGameObject * obj, stDisplayPosition * pos, float objSize){
    float x, y;
    // create object 
    switch (obj->type)
    {
    case Ball:
        //load ball sprite
        sprite.setTexture(ball);
        x = 600;
        y = 600;
        break;
    case Hole:
        //load hole sprite
        sprite.setTexture(hole);
        x = 476;
        y = 456;
        break;
    case Spike:
        //load spike sprite
        sprite.setTexture(spike);
        x = 554;
        y = 554;
        break;
    case Block:
        //load block sprite
        sprite.setTexture(block);
        x = 400;
        y = 400;
        break;
    default:
        //don't load sprite
        break;

    }

    sprite.setScale(objSize / x, objSize / y);
    sprite.setColor(sf::Color(obj->color.r, obj->color.g, obj->color.b));
    sprite.setPosition(sf::Vector2f(pos->x, pos->y));
    window->draw(sprite);
}
