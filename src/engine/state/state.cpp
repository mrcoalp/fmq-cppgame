#include "state.h"

State::State(sf::RenderWindow *window)
{
    this->_window = window;
    this->_quit = false;
    this->_nrOfCredits = 0;
}

State::~State()
{
    //dtor
}

const bool &State::getQuit() const
{
    return this->_quit;
}

void State::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->_quit = true;
}