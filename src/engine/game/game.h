#ifndef GAME_H
#define GAME_H

#include "../../engine/state/gamestate.h"

class Game {
   public:
    Game();
    ~Game();

    /**
     * Runs game
     * Initializes game loop
     */
    void run();

   protected:
   private:
    sf::RenderWindow* _window;
    sf::Event _sfEvent;
    // delta time
    // keeps track of time needed for one game loop
    sf::Clock _dtClock;
    float _dt;
    GameState* _state;

    /**
     * Sets up a game window
     * Uses SFML graphics library
     */
    void _setupWindow();
    /**
     * Sets up a new game state
     */
    void _setupState();
    /**
     * Checks for events occured in sfml
     */
    void _checkSFMLEvents();
    /**
     * Checks for user input
     */
    void _checkKeyboardActions();
    /**
     * Checks for user input
     */
    void _checkMouseActions();
    /**
     * Updates delta time
     */
    void _updateDeltaTime();
    /**
     * Updates game state
     */
    void _update();
    /**
     * Renders game objects
     */
    void _render();
};

#endif   // GAME_H
