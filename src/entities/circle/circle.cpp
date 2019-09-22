#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Color color, int radius) : Entity(x, y, speed)
{
    this->_shape = new sf::CircleShape(radius);
    this->_createMovement(speed, static_cast<float>((rand() % 2 + 1) * 10));
    this->_shape->setFillColor(color);
    this->_shape->setPosition(x, y);
    this->_grow = true;
}

Circle::~Circle()
{
    std::cout << "circle cleared\n";
}

void Circle::animate()
{
    // this->_grow ? this->_shape->scale(2, 2) : this->_shape->scale(0.5, 0.5);
    // this->_grow = !this->_grow;
}