#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../../headers/sfml.h"
#include "../../entities/circle/circle.h"
#include "../../entities/rectangle/rectangle.h"
#include <stack>
#include <iostream>
#include <algorithm> // std::all_of

class GameState
{
public:
    GameState(sf::RenderWindow *window);
    ~GameState();

    void update(const float &dt);
    void render(sf::RenderTarget *target = NULL);
    void startGame();
    void setAnimating();
    void addCredit();

protected:
private:
    sf::RenderWindow *_window;
    std::map<std::string, sf::Texture> _textures;
    sf::Music _backgroundMusic;
    sf::Sprite *_backgroundSprite;
    int _nrOfCredits;
    bool _animating;
    std::vector<Entity *> _entities;

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
     * Initializes game entities or resets them after a play
     */
    void _initOrResetEntities();
    /**
     * Starts the music in the background
     */
    void _startBackgroundMusic();

    //methods used to provide random values to entities
    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif // GAMESTATE_H
