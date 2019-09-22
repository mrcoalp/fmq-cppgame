#ifndef TEXTURE_H
#define TEXTURE_H

#include "../entity.h"

class Texture : public Entity
{
public:
    Texture(int x, int y, int speed, sf::Texture *texture);
    virtual ~Texture();

    void move(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target);
    bool checkCollision();

protected:
private:
    sf::Sprite _sprite;
};

#endif // TEXTURE_H
