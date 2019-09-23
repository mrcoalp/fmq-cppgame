#include "entity.h"

Entity::Entity(int x, int y, int speed, sf::Texture *texture)
{
    this->_shape = NULL;
    this->_movement = NULL;
    this->_texture = texture;
    this->_hasAnimationFinished = false;
    this->_direction_x = this->_getRandomDirection();
    this->_direction_y = this->_getRandomDirection();
}

Entity::~Entity()
{
    delete this->_movement;
    std::cout << "entity cleared\n";
}

void Entity::move(const float &dt)
{
    //movement component updates entity position
    this->_movement->move(this->_direction_x, this->_direction_y, dt);
}

void Entity::update(const float &dt)
{
    this->_movement->update(dt);
    this->animate();
    //when entity collides with window border, animation finishes
    if (this->_checkCollision())
        this->_hasAnimationFinished = true;
}

void Entity::render(sf::RenderTarget *target)
{
    //draws shape in render target
    //passed as argument from gamestate
    target->draw(*this->_shape);
}

void Entity::_createMovement(const float speed)
{
    this->_movement = new MovementComponent(speed, this->_shape);
}

bool Entity::_checkCollision()
{
    //define hitbox
    //TODO(marco): maybe as a property?
    std::map<std::string, float> hitbox;
    hitbox["LEFT"] = this->_shape->getPosition().x;
    hitbox["RIGHT"] = this->_shape->getPosition().x + this->_shape->getGlobalBounds().width;
    hitbox["UP"] = this->_shape->getPosition().y;
    hitbox["DOWN"] = this->_shape->getPosition().y + this->_shape->getGlobalBounds().height;
    //checks if entity hitbox collides with window border
    return !(hitbox["LEFT"] > 0 && hitbox["RIGHT"] < WINDOW_WIDTH && hitbox["UP"] > 0 && hitbox["DOWN"] < WINDOW_HEIGHT);
}

float Entity::_getRandomDirection()
{
    //define difference between min and max values possible
    float diff = 1.0 - 0.3;
    //return a float between 0.3 and 1 multiplied either by -1 or 1
    //this ensure that the movement is never 'too slow'
    return (((static_cast<float>(rand()) / RAND_MAX) * diff) + 0.3) * (rand() % 2 == 0 ? 1 : -1);
}

const bool &Entity::getHasAnimationFinished() const
{
    return this->_hasAnimationFinished;
}