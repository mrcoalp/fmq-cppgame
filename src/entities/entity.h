#ifndef ENTITY_H
#define ENTITY_H

#include "../headers/sfml.h"
#include "../constants.h"
#include <iostream>

class Entity
{
public:
    Entity(int x, int y, int speed);
    virtual ~Entity();

    /**
     * Updates entity position
     */
    virtual void move(const float &dt) = 0;
    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
    /**
     * Checks entity collision with window boundaries
     */
    virtual bool checkCollision() = 0;
    virtual const bool &getHasAnimationFinished() const;

protected:
    float _direction_x;
    float _direction_y;
    float _speed;
    bool _hasAnimationFinished;

    /**
     * Returns a random float between -1 and 1
     */
    float _getRandomDirection();

private:
};

#endif // ENTITY_H
