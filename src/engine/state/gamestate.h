#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../headers/sfml.h"
#include "../../entities/circle/circle.h"
#include "../../entities/rectangle/rectangle.h"
#include <stack>
#include <iostream>

class GameState
{
public:
    GameState(sf::RenderWindow *window);
    ~GameState();

    const bool &getQuit() const;

    void update(const float &dt);
    void render(sf::RenderTarget *target = NULL);
    void startGame();

protected:
private:
    sf::RenderWindow *_window;
    bool _quit;
    int _nrOfCredits;
    bool _animating;
    std::vector<Entity *> _entities;

    void _initGameState();
    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif // GAMESTATE_H
