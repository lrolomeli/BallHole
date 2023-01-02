#include "GameObject.h"

void displacement(uint8_t direction, stGameObject * selectedBall, stGameObject * board, stBallEvent *ev);
bool isThereABall(uint8_t objType);
uint8_t getClickBox(float mouse_x, float mouse_y, float scrdim);
void pickingBall(float mouse_x, float mouse_y, float scrdim, stGameObject * board, stGameObject * selectedBall);
void unselectBall(stGameObject * selectedBall);
void selectBall(stGameObject * board, stGameObject * selectedBall, uint8_t box);