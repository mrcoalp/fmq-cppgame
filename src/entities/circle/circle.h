#ifndef CIRCLE_H
#define CIRCLE_H

#include "entities/entity.h"

class Circle : public Entity {
public:
    Circle(int x, int y, int speed, sf::Texture* texture, sf::Color color, int radius);
    virtual ~Circle();

    virtual void animate();

protected:
private:
    float _scale;
    bool _grow;
};

#endif  // CIRCLE_H
