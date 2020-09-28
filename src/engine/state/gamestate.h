#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <algorithm>  // std::all_of
#include <iostream>
#include <sstream>
#include <stack>

#include "entities/circle/circle.h"
#include "entities/rectangle/rectangle.h"
#include "gui/gui.h"
#include "headers/sfml.h"

class GameState {
public:
    GameState(sf::RenderWindow* window);
    ~GameState();

    std::map<std::string, gui::Button*> buttons;

    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void startOrPauseGame();
    void addCredit();
    void removeCredits();

protected:
private:
    sf::RenderWindow* _window;
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;
    sf::Music _backgroundMusic;
    std::map<std::string, sf::Sprite*> _sprites;
    bool _animating;
    bool _gameInProgress;
    std::vector<Entity*> _entities;
    int _nrOfCredits;
    int _totalInCredits;
    int _totalOutCredits;
    int _nrOfPlays;
    std::map<std::string, sf::Text> _texts;

    /**
     * Inits all gamestate variables
     */
    void _initGameState();
    /**
     * Loads all textures and sounds needed for game
     */
    void _loadAssets();
    /**
     * Initializes sprites with relative textures
     */
    void _initSprites();
    /**
     * Initializes buttons
     */
    void _initButtons();
    /**
     * Initiales texts
     */
    void _initTexts();
    /**
     * Updates texts to match current values
     */
    void _updateTexts();
    /**
     * Initializes game entities or resets them after a play
     */
    void _initOrResetEntities();
    /**
     * Starts the music in the background
     */
    void _startBackgroundMusic();
    void _checkIfPlayFinished();

    // methods used to provide random values to entities
    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif  // GAMESTATE_H
