#include "menustate.h"

MenuState::MenuState(sf::RenderWindow *window) : State(window)
{
    //ctor
}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void MenuState::update(const float &dt)
{
    this->updateKeybinds(dt);
}

void MenuState::render(sf::RenderTarget *target)
{
}