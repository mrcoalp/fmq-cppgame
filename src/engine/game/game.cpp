#include "game.h"
#include <iostream>
#include "../../constants.h"

Game::Game()
{
    //setup window and state
    this->_setupWindow();
    this->_setupState();
}

Game::~Game()
{
    delete this->_window;
    delete this->_state;
    std::cout << "game cleared\n";
}

void Game::_setupWindow()
{
    //new window
    //sf::Style::Close disables resizing of the window
    //TODO(marco): maybe enable resize later if there is time...
    this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FMQ", sf::Style::Close);
}

void Game::_setupState()
{
    this->_state = new GameState(this->_window);
}

void Game::_checkSFMLEvents()
{
    while (this->_window->pollEvent(this->_sfEvent))
    {
        if (this->_sfEvent.type == sf::Event::Closed)
            this->_window->close();
        if (this->_sfEvent.type == sf::Event::KeyPressed)
        {
            if (this->_sfEvent.key.code == sf::Keyboard::Space)
            {
                std::cout << "new game or pause current" << std::endl;
                this->_state->setAnimating();
            }
            else if (this->_sfEvent.key.code == sf::Keyboard::I)
                this->_state->addCredit();
        }
    }
}

void Game::_updateDeltaTime()
{
    //updates dt with the time it takes to update and render one frame
    this->_dt = this->_dtClock.restart().asSeconds();
}

void Game::_update()
{
    this->_checkSFMLEvents();
    this->_updateDeltaTime();
    this->_state->update(this->_dt);
}

void Game::_render()
{
    this->_window->clear();
    this->_state->render(this->_window);
    this->_window->display();
}

void Game::run()
{
    //sets the maximum framerate
    this->_window->setFramerateLimit(60);
    //prevents repetition of key strokes
    //we only have single event actions, not repetitive ones like
    //player movement
    this->_window->setKeyRepeatEnabled(false);
    //while window is open run the game
    //updates state and renders objects
    while (this->_window->isOpen())
    {
        this->_update();
        this->_render();
    }
}