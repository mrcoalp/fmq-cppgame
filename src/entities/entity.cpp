#include "entity.h"

Entity::Entity(int x, int y, int speed)
{
    this->_shape = NULL;
    this->_movement = NULL;
    this->_hasAnimationFinished = false;
    this->_direction_x = this->_getRandomDirection();
    this->_direction_y = this->_getRandomDirection();
}

Entity::~Entity()
{
    // delete this->_shape;
    delete this->_movement;
    std::cout << "entity cleared\n";
}

void Entity::move(const float &dt)
{
    this->_movement->move(this->_direction_x, this->_direction_y, dt);
}

void Entity::update(const float &dt)
{
    if (this->_checkCollision())
        this->_hasAnimationFinished = true;

    this->_movement->update(dt);
    this->animate();
}

void Entity::render(sf::RenderTarget *target)
{
    //draws shape in render target
    //passed as argument from gamestate
    target->draw(*this->_shape);
}

void Entity::_createMovement(const float speed, const float acceleration)
{
    this->_movement = new MovementComponent(speed, this->_shape, acceleration);
}

bool Entity::_checkCollision()
{
    return !(this->_shape->getPosition().x > 0 && this->_shape->getPosition().x + this->_shape->getGlobalBounds().width < WINDOW_WIDTH && this->_shape->getPosition().y > 0 && this->_shape->getPosition().y + this->_shape->getGlobalBounds().height < WINDOW_HEIGHT);
}

float Entity::_getRandomDirection()
{
    float diff = 1.0 - 0.3;
    return (((static_cast<float>(rand()) / RAND_MAX) * diff) + 0.3) * (rand() % 2 == 0 ? 1 : -1);
}

const bool &Entity::getHasAnimationFinished() const
{
    return this->_hasAnimationFinished;
}