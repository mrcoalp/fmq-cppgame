#ifndef CIRCLE_H
#define CIRCLE_H

#include "../shapeentity.h"

class Circle : public ShapeEntity
{
public:
    Circle(int x, int y, int speed, sf::Color color, int radius);
    virtual ~Circle();

protected:
private:
};

#endif // CIRCLE_H
