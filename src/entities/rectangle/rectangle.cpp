#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int speed, sf::Texture* texture,
                     sf::Color color, float width, float height)
    : Entity(x, y, speed, texture) {
    this->_shape = new sf::RectangleShape(sf::Vector2f(width, height));
    this->_shape->setPosition(x, y);
    this->_createMovement(speed);
    this->_shape->setTexture(texture);
    this->_shape->setFillColor(color);
    this->_shape->setOrigin(sf::Vector2f(width / 2, height / 2));
}

Rectangle::~Rectangle() {}

void Rectangle::animate() {     // rectangles will rotate over time
    this->_shape->rotate(10);   // rotate 10º in each update of the game
}