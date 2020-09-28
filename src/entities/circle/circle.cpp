#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Texture* texture, sf::Color color, int radius) : Entity(x, y, speed, texture) {
    _shape = new sf::CircleShape(radius);
    _createMovement(speed);
    _shape->setPosition(x, y);
    _scale = 1.0;
    _grow = true;
    _shape->setTexture(texture);
    _shape->setFillColor(color);
    _shape->setOrigin(sf::Vector2f(radius, radius));
}

Circle::~Circle() {}

void Circle::animate() {  // circles will increase and decrease size over time
    if (_grow)            // if circle is growing, increment scale
        _scale += 0.01;
    else if (!_grow)  // else decrement
        _scale -= 0.01;
    // set max and min scale
    // change grow property accordingly
    if (_shape->getScale().x >= 1.3 && _shape->getScale().y >= 1.3)
        _grow = false;
    else if (_shape->getScale().x <= 1.0 && _shape->getScale().y <= 1.0)
        _grow = true;

    _shape->setScale(sf::Vector2f(_scale, _scale));  // set scale
}