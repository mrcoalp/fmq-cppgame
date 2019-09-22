#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "../../headers/sfml.h"
#include <iostream>

class MovementComponent
{
public:
    MovementComponent(float maxVelocity, sf::Shape *shape, float acceleration);
    virtual ~MovementComponent();

    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);

protected:
private:
    float _maxVelocity;
    sf::Vector2f _velocity;
    float _acceleration;
    sf::Shape *_shape;
};

#endif // MOVEMENTCOMPONENT_H
