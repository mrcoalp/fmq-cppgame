#ifndef ENTITY_H
#define ENTITY_H

#include "../headers/sfml.h"
#include "../constants.h"
#include <iostream>
#include "../engine/movement/movementcomponent.h"

class Entity
{
public:
    Entity(int x, int y, int speed);
    virtual ~Entity();

    /**
     * Updates entity position
     */
    virtual void move(const float &dt);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target = NULL);
    virtual const bool &getHasAnimationFinished() const;
    /**
     * Animates object
     * Method to be implemented in child classes
     * Each one has a different animation
     */
    virtual void animate() = 0;

protected:
    sf::Shape *_shape;
    MovementComponent *_movement;

    void _createMovement(const float speed, const float acceleration);

private:
    float _direction_x;
    float _direction_y;
    bool _hasAnimationFinished;

    /**
     * Checks entity collision with window boundaries
     */
    bool _checkCollision();
    /**
     * Returns a random float between -1 and 1
     */
    float _getRandomDirection();
};

#endif // ENTITY_H
