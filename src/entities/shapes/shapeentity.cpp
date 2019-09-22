#include "shapeentity.h"

ShapeEntity::ShapeEntity(int x, int y, int speed, sf::Color color) : Entity(x, y, speed)
{
    //ctor
}

ShapeEntity::~ShapeEntity()
{
    delete this->_shape;
    std::cout << "shape cleared\n";
}

void ShapeEntity::move(const float &dt)
{
    //initialize directions if null
    this->_direction_x = this->_direction_x ? this->_direction_x : this->_getRandomDirection();
    this->_direction_y = this->_direction_y ? this->_direction_y : this->_getRandomDirection();
    //change directions if entity collides with window boundaries
    if (this->checkCollision())
    {
        this->_hasAnimationFinished = true;
    }
    //move entity if animation not finished
    this->_shape->move(this->_direction_x * this->_speed * dt, this->_direction_y * this->_speed * dt);
}

void ShapeEntity::update(const float &dt)
{
    if (!this->_hasAnimationFinished)
    {

        this->move(dt);
        this->animate();
    }
}

void ShapeEntity::render(sf::RenderTarget *target)
{
    //draws shape in render target
    //passed as argument from gamestate
    target->draw(*this->_shape);
}

bool ShapeEntity::checkCollision()
{
    return !(this->_shape->getPosition().x > 0 && this->_shape->getPosition().x + this->_shape->getGlobalBounds().width < WINDOW_WIDTH && this->_shape->getPosition().y > 0 && this->_shape->getPosition().y + this->_shape->getGlobalBounds().height < WINDOW_HEIGHT);
}