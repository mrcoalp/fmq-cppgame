#include "texture.h"

Texture::Texture(int x, int y, int speed, sf::Texture *texture) : Entity(x, y, speed)
{
    this->_sprite.setTexture(*texture);
    this->_sprite.setPosition(x, y);
}

Texture::~Texture()
{
}

void Texture::move(const float &dt)
{
    //initialize directions if null
    this->_direction_x = this->_direction_x ? this->_direction_x : this->_getRandomDirection();
    this->_direction_y = this->_direction_y ? this->_direction_y : this->_getRandomDirection();
    //change directions if entity collides with window boundaries
    if (this->checkCollision())
    {
        this->_hasAnimationFinished = true;
    }
    //move entity
    if (!this->_hasAnimationFinished)
        this->_sprite.move(this->_direction_x * this->_speed * dt, this->_direction_y * this->_speed * dt);
}

void Texture::update(const float &dt)
{
    this->move(dt);
}

void Texture::render(sf::RenderTarget *target)
{
    //draws shape in render target
    //passed as argument from gamestate
    target->draw(this->_sprite);
}

bool Texture::checkCollision()
{
    return !(this->_sprite.getPosition().x > 0 && this->_sprite.getPosition().x + this->_sprite.getGlobalBounds().width < WINDOW_WIDTH && this->_sprite.getPosition().y > 0 && this->_sprite.getPosition().y + this->_sprite.getGlobalBounds().height < WINDOW_HEIGHT);
}