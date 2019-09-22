#ifndef GAME_H
#define GAME_H

#include "../../engine/state/state.h"
#include "../../engine/state/game-state/gamestate.h"

class Game
{
public:
    Game();
    ~Game();

    /**
     * Updates events occured in sfml
     */
    void updateSFMLEvents();
    /**
     * Updates game state
     */
    void update();
    /**
     * Renders game objects
     */
    void render();
    /**
     * Runs game
     * Initializes game loop
     */
    void run();
    void updateDeltaTime();

protected:
private:
    sf::RenderWindow *_window;
    sf::Event _sfEvent;
    //delta time
    //keeps track of time needed for one game loop
    sf::Clock _dtClock;
    float _dt;
    std::stack<State *> _states;

    /**
     * Setups game window
     * Uses SFML graphics library
     */
    void _setupWindow();
    void _setupStates();
};

#endif // GAME_H
