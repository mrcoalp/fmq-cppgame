#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    Position(int x, int y);
    int x;
    int y;
};

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

#endif