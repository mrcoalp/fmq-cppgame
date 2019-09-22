#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../headers/sfml.h"
#include "../../entities/entity.h"
#include "../../entities/shapes/circle/circle.h"
#include "../../entities/shapes/rectangle/rectangle.h"
#include "../../entities/texture/texture.h"
#include <stack>
#include <iostream>

class GameState
{
public:
    GameState(sf::RenderWindow *window);
    ~GameState();

    const bool &getQuit() const;

    void update();
    void render(sf::RenderTarget *target = NULL);

protected:
private:
    sf::RenderWindow *_window;
    bool _quit;
    int _nrOfCredits;
    bool _animating;
    std::vector<Entity *> *_entities;

    void _checkForInput();
    void _initGameState();
    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif // GAMESTATE_H
