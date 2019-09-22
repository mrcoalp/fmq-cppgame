#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int speed, sf::Color color, float width, float height) : ShapeEntity(x, y, speed, color)
{
    this->_shape = new sf::RectangleShape(sf::Vector2f(width, height));
    this->_shape->setFillColor(color);
    this->_shape->setPosition(x, y);
}

Rectangle::~Rectangle()
{
    //dtor
}
