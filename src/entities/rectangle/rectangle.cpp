#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int speed, sf::Texture* texture, sf::Color color, float width, float height) : Entity(x, y, speed, texture) {
    _shape = new sf::RectangleShape(sf::Vector2f(width, height));
    _shape->setPosition(x, y);
    _createMovement(speed);
    _shape->setTexture(texture);
    _shape->setFillColor(color);
    _shape->setOrigin(sf::Vector2f(width / 2, height / 2));
}

Rectangle::~Rectangle() {}

void Rectangle::animate() {  // rectangles will rotate over time
    _shape->rotate(10);      // rotate 10º in each update of the game
}