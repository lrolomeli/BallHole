#include "GameObject.h"

GameObject::GameObject()
{
    this->position = 0;
    this->type = enGameObjType::None;
}

GameObject::GameObject(uint8_t position, enGameObjType type)
{
    this->position = position;
    this->type = type;
}

GameObject::~GameObject()
{

}

void GameObject::setPosition(uint8_t position)
{
    this->position = position;
}

uint8_t * GameObject::getPosition()
{
    return &(this->position);
}

enGameObjType GameObject::getObjType()
{
    return this->type;
}