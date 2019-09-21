#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Game
{
public:
    Game();
    virtual ~Game();

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
    sf::RenderWindow *window;
    sf::Event sfEvent;
    //delta time
    //keeps track of time needed for one game loop
    sf::Clock dtClock;
    float dt;

    /**
     * Setups game window
     * Uses SFML graphics library
     */
    void setupWindow();
};

#endif // GAME_H
