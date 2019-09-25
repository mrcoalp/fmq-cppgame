#include "movementcomponent.h"

MovementComponent::MovementComponent(float maxVelocity, sf::Shape* shape) {
    this->_maxVelocity = maxVelocity;
    this->_shape = shape;
}

MovementComponent::~MovementComponent() { delete this->_shape; }

void MovementComponent::move(const float dir_x, const float dir_y,
                             const float& dt) {
    this->_velocity.x = dir_x * this->_maxVelocity;
    this->_velocity.y = dir_y * this->_maxVelocity;
}

void MovementComponent::update(const float& dt) {
    this->_shape->move(this->_velocity * dt);
}
