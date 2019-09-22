#include "entity.h"

Entity::Entity(int x, int y, int speed)
{
    this->_speed = speed;
    this->_hasAnimationFinished = false;
}

Entity::~Entity()
{
    std::cout << "entity cleared\n";
}

float Entity::_getRandomDirection()
{
    //returns a random float that define direction
    return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (rand() % 2 == 0 ? 1 : -1);
}

const bool &Entity::getHasAnimationFinished() const
{
    return this->_hasAnimationFinished;
}