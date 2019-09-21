#include "game.h"
#include <iostream>

Game::Game()
{
    this->setupWindow();
}

Game::~Game()
{
    delete this->window;
}

void Game::setupWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "FMQ");
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::updateDeltaTime()
{
    //updates dt with the time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
    system("clear");
    std::cout << this->dt << std::endl;
}

void Game::update()
{
    this->updateSFMLEvents();
    this->updateDeltaTime();
}

void Game::render()
{
    this->window->clear();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();

        this->render();
    }
}