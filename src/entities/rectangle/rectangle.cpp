#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int speed, sf::Texture *texture, sf::Color color, float width, float height) : Entity(x, y, speed, texture)
{
    this->_shape = new sf::RectangleShape(sf::Vector2f(width, height));
    this->_shape->setPosition(x, y);
    this->_createMovement(speed);
    this->_shape->setTexture(texture);
    this->_shape->setFillColor(color);
}

Rectangle::~Rectangle()
{
    std::cout << "rectangle cleared\n";
}

void Rectangle::animate()
{
    this->_shape->rotate(10);
}