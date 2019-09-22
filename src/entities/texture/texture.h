#ifndef TEXTURE_H
#define TEXTURE_H

#include "../entity.h"

class Texture : public Entity
{
public:
    Texture(int x, int y, int speed, sf::Color color);
    virtual ~Texture();

    virtual void move();
    virtual void update();
    virtual void render(sf::RenderTarget *target = NULL);
    virtual bool checkCollision();
    virtual void animate();

protected:
private:
    sf::Texture *_texture;
    sf::Sprite _sprite;
};

#endif // TEXTURE_H
