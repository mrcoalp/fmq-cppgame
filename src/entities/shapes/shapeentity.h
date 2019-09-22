#ifndef SHAPEENTITY_H
#define SHAPEENTITY_H

#include "../entity.h"

class ShapeEntity : public Entity
{
public:
    ShapeEntity(int x, int y, int speed, sf::Color color);
    ~ShapeEntity();

    virtual void move(const float &dt);
    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target = NULL);
    virtual bool checkCollision();
    virtual void animate() = 0;

protected:
    sf::Shape *_shape;

private:
};

#endif // SHAPEENTITY_H
