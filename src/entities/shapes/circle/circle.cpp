#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Color color, int radius) : ShapeEntity(x, y, speed, color)
{
    this->_shape = new sf::CircleShape(radius);
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