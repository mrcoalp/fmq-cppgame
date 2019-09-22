#include "game.h"
#include <iostream>

#include "../../constants.h"

Game::Game()
{
    //setup window, states
    this->_setupWindow();
    this->_setupStates();
}

Game::~Game()
{
    delete this->_window;

    while (!this->_states.empty())
    {
        delete this->_states.top();
        this->_states.pop();
    }
}

void Game::_setupWindow()
{
    //new 800x600 window
    this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FMQ");
}

void Game::_setupStates()
{
    this->_states.push(new GameState(this->_window));
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

    if (this->_states.empty())
        this->_window->close();
    else
    {
        this->_states.top()->update(this->_dt);

        if (this->_states.top()->getQuit())
        {
            delete this->_states.top();
            this->_states.pop();
        }
    }
}

void Game::render()
{
    this->_window->clear();

    if (!this->_states.empty())
        this->_states.top()->render(this->_window);

    this->_window->display();
}

void Game::run()
{
    while (this->_window->isOpen())
    {
        this->update();
        this->render();
    }
}