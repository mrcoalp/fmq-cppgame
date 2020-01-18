#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <iostream>
#include "headers/sfml.h"

class MovementComponent {
   public:
    MovementComponent(float maxVelocity, sf::Shape* shape);
    virtual ~MovementComponent();

    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);

   protected:
   private:
    float _maxVelocity;
    sf::Vector2f _velocity;
    sf::Shape* _shape;
};

#endif   // MOVEMENTCOMPONENT_H
