#include "movementcomponent.h"

MovementComponent::MovementComponent(float maxVelocity, sf::Shape* shape) {
    _maxVelocity = maxVelocity;
    _shape = shape;
}

MovementComponent::~MovementComponent() { delete _shape; }

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt) {
    _velocity.x = dir_x * _maxVelocity;
    _velocity.y = dir_y * _maxVelocity;
}

void MovementComponent::update(const float& dt) { _shape->move(_velocity * dt); }
