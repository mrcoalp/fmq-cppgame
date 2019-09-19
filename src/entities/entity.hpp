#ifndef ENTITY_H
#define ENTITY_H
#include "../helpers/helpers.hpp"

class Entity
{
private:
    Position _position;

public:
    Entity(int x, int y) : _position(x, y) {}

    Position getPosition()
    {
        return this->_position;
    }
};

#endif