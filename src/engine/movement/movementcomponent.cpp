#include "movementcomponent.h"

MovementComponent::MovementComponent(float maxVelocity, sf::Shape *shape, float acceleration)
{
    this->_maxVelocity = maxVelocity;
    this->_shape = shape;
    this->_acceleration = acceleration;
}

MovementComponent::~MovementComponent()
{
    delete this->_shape;
}

const sf::Vector2f &MovementComponent::getVelocity() const
{
    return this->_velocity;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
    //adds acceleration to the movement
    //object keeps gaining speed until reaching max velocity
    this->_velocity.x += dir_x * this->_acceleration; //update velocity in x axis
    //checks to never surpass max velocity
    if (this->_velocity.x > 0.f && this->_velocity.x > this->_maxVelocity) //right
        this->_velocity.x = this->_maxVelocity;
    else if (this->_velocity.x < 0.f && this->_velocity.x < -this->_maxVelocity) //left
        this->_velocity.x = -this->_maxVelocity;

    this->_velocity.y += dir_y * this->_acceleration; //update velocity in y axis
    if (this->_velocity.y > 0.f && this->_velocity.y > this->_maxVelocity) //down
        this->_velocity.y = this->_maxVelocity;
    else if (this->_velocity.y < 0.f && this->_velocity.y < -this->_maxVelocity) //up
        this->_velocity.y = -this->_maxVelocity;
}

void MovementComponent::update(const float &dt)
{
    this->_shape->move(this->_velocity * dt);
}
