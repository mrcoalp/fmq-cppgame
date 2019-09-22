#ifndef CIRCLE_H
#define CIRCLE_H

#include "../entity.h"

class Circle : public Entity
{
public:
    Circle(int x, int y, int speed, sf::Color color, int radius);
    virtual ~Circle();

    virtual void animate();

protected:
private:
    //used to determine if object must grow or shrink in size
    bool _grow;
};

#endif // CIRCLE_H
