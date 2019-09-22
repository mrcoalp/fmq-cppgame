#include "game.h"
#include <iostream>
#include "../../constants.h"

Game::Game()
{
    //setup window, state
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
    this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FMQ");
}

void Game::_setupState()
{
    this->_state = new GameState(this->_window);
}

void Game::updateSFMLEvents()
{
    while (this->_window->pollEvent(this->_sfEvent))
    {
        if (this->_sfEvent.type == sf::Event::Closed)
            this->_window->close();
    }
}

void Game::updateDeltaTime()
{
    //updates dt with the time it takes to update and render one frame
    this->_dt = this->_dtClock.restart().asSeconds();
}

void Game::update()
{
    this->updateSFMLEvents();
    this->updateDeltaTime();

    if (this->_state->getQuit())
        this->_window->close();
    else
        this->_state->update(this->_dt);
}

void Game::render()
{
    this->_window->clear();
    this->_state->render(this->_window);
    this->_window->display();
}

void Game::run()
{
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(false);
    while (this->_window->isOpen())
    {
        this->update();
        this->render();
    }
}