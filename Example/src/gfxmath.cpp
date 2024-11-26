#include "GFXMath.hpp"

Vector2f::Vector2f() : x(0), y(0) {}

Vector2f::Vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}

void Vector2f::print() {
    std::cout << x << ", " << y << std::endl;
}

float& Vector2f::getVx() {
    return x;
}
float& Vector2f::getVy() {
    return y;
}

Vector2f v2f;
Vector2f v2f_0(0,0);