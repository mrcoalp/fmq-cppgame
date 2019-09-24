#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../headers/sfml.h"
#include "../../entities/circle/circle.h"
#include "../../entities/rectangle/rectangle.h"
#include <stack>
#include <iostream>
#include <algorithm> // std::all_of
#include "../../gui/gui.h"
#include <sstream> 

class GameState
{
public:
    GameState(sf::RenderWindow *window);
    ~GameState();

    std::map<std::string, gui::Button *> buttons;

    void update(const float &dt);
    void render(sf::RenderTarget *target = NULL);
    void startOrPauseGame();
    void addCredit();
    void removeCredits();

protected:
private:
    sf::RenderWindow *_window;
    std::map<std::string, sf::Texture> _textures;
    sf::Music _backgroundMusic;
    std::map<std::string, sf::Sound> _sounds;
    sf::Sprite *_backgroundSprite;
    sf::Sprite *_fmqLogo;
    int _nrOfCredits;
    bool _animating;
    bool _gameInProgress;
    std::vector<Entity *> _entities;
    std::map<std::string, sf::Font> _fonts;
    sf::Text _textNrOfCredits;

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
     * Initializes game entities or resets them after a play
     */
    void _initTexts();
    void _initOrResetEntities();
    /**
     * Starts the music in the background
     */
    void _startBackgroundMusic();
    void _checkIfPlayFinished();

    //methods used to provide random values to entities
    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif // GAMESTATE_H
