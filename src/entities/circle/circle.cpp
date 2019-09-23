#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Texture *texture, sf::Color color, int radius) : Entity(x, y, speed, texture)
{
    this->_shape = new sf::CircleShape(radius);
    this->_createMovement(speed);
    this->_shape->setPosition(x, y);
    this->_grow = true;
    this->_shape->setTexture(texture);
    this->_shape->setFillColor(color);
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