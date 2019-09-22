#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../shapeentity.h"

class Rectangle : public ShapeEntity
{
public:
    Rectangle(int x, int y, int speed, sf::Color color, float width, float height);
    virtual ~Rectangle();

    virtual void animate();

protected:
private:
};

#endif // RECTANGLE_H
