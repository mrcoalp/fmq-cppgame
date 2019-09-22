#include "texture.h"

Texture::Texture(int x, int y, int speed, sf::Color color) : Entity(x, y, speed)
{
    this->_texture = new sf::Texture;
    if (this->_texture->loadFromFile("/home/marco/Development/fmq-cppgame/src/assets/fmq.png"))
    {
        this->_texture->setSmooth(true);
        this->_sprite.setTexture(*this->_texture);
        this->_sprite.setColor(color);
        this->_sprite.setPosition(x, y);
    }
}

Texture::~Texture()
{
    delete this->_texture;
    std::cout << "texture cleared\n";
}

void Texture::move()
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
    this->_sprite.move(this->_direction_x * this->_speed, this->_direction_y * this->_speed);
}

void Texture::update()
{
    if (!this->_hasAnimationFinished)
    {
        this->move();
        this->animate();
    }
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

void Texture::animate() {}