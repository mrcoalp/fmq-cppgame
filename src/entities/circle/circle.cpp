#include "circle.h"

Circle::Circle(int x, int y, int speed, sf::Texture* texture, sf::Color color,
               int radius)
    : Entity(x, y, speed, texture) {
    this->_shape = new sf::CircleShape(radius);
    this->_createMovement(speed);
    this->_shape->setPosition(x, y);
    this->_scale = 1.0;
    this->_grow = true;
    this->_shape->setTexture(texture);
    this->_shape->setFillColor(color);
    this->_shape->setOrigin(sf::Vector2f(radius, radius));
}

Circle::~Circle() {}

void Circle::animate() {   // circles will increase and decrease size over time
    if (this->_grow)       // if circle is growing, increment scale
        this->_scale += 0.01;
    else if (!this->_grow)   // else decrement
        this->_scale -= 0.01;
    // set max and min scale
    // change grow property accordingly
    if (this->_shape->getScale().x >= 1.3 && this->_shape->getScale().y >= 1.3)
        this->_grow = false;
    else if (this->_shape->getScale().x <= 1.0 &&
             this->_shape->getScale().y <= 1.0)
        this->_grow = true;

    this->_shape->setScale(
        sf::Vector2f(this->_scale, this->_scale));   // set scale
}