#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../entity.h"

class Rectangle : public Entity
{
public:
    Rectangle(int x, int y, int speed, sf::Color color, float width, float height);
    virtual ~Rectangle();

    virtual void animate();

protected:
private:
};

#endif // RECTANGLE_H
