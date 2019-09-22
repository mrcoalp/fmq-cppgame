#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Color color, int radius) : ShapeEntity(x, y, speed, color)
{
    this->_shape = new sf::CircleShape(radius);
    this->_shape->setFillColor(color);
    this->_shape->setPosition(x, y);
}

Circle::~Circle()
{
}
