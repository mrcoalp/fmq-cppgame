#ifndef TEXTURE_H
#define TEXTURE_H

#include "../entity.h"

class Texture : public Entity
{
public:
    Texture(int x, int y, int speed, sf::Color color);
    ~Texture();

    void move(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = NULL);
    bool checkCollision();
    void animate();

protected:
private:
    sf::Texture *_texture;
    sf::Sprite _sprite;
};

#endif // TEXTURE_H
