#ifndef CIRCLE_H
#define CIRCLE_H

#include "../shapeentity.h"

class Circle : public ShapeEntity
{
public:
    Circle(int x, int y, int speed, sf::Color color, int radius);
    ~Circle();

    void animate();

protected:
private:
    //used to determine if object must grow or shrink in size
    bool _grow;
};

#endif // CIRCLE_H
