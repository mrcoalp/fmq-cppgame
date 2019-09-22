#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window)
{
    srand(time(NULL));
    std::cout << "gamestate init\n";
    this->_window = window;
    this->_quit = false;
    this->_nrOfCredits = 0;
    this->_animating = false;
}

GameState::~GameState()
{
    for (std::vector<Entity *>::iterator i = this->_entities->begin(); i != this->_entities->end(); ++i)
        delete (*i);
    delete this->_entities;
    std::cout << "game state cleared\n";
}

void GameState::_initGameState()
{
    this->_entities = new std::vector<Entity *>();
    int counter = 50;
    while (counter > 0)
    {
        if (counter < 25)
            this->_entities->push_back(new Circle(640, 360, 5, this->_getRandomColor(), this->_getRandomSize()));
        else
            this->_entities->push_back(new Rectangle(640, 360, 4, this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
        --counter;
    }
    // this->_entities->push_back(new Texture(640, 360, this->_getRandomSpeed(), this->_getRandomColor()));
    this->_animating = true;
}

const bool &GameState::getQuit() const
{
    return this->_quit;
}

void GameState::_checkForInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->_quit = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        this->_initGameState();
}

void GameState::update()
{
    this->_checkForInput();

    if (this->_animating)
        for (std::vector<Entity *>::iterator i = this->_entities->begin(); i != this->_entities->end(); ++i)
            (*i)->update();
}

void GameState::render(sf::RenderTarget *target)
{
    if (this->_animating)
        for (std::vector<Entity *>::iterator i = this->_entities->begin(); i != this->_entities->end(); ++i)
            (*i)->render(target);
}

sf::Color GameState::_getRandomColor()
{
    switch (rand() % 5)
    {
    case 0:
        return sf::Color::Blue;
    case 1:
        return sf::Color::Green;
    case 2:
        return sf::Color::Magenta;
    case 3:
        return sf::Color::Yellow;
    case 4:
        return sf::Color::Red;
    default:
        return sf::Color::Cyan;
    }
}

int GameState::_getRandomSpeed()
{
    //returns 100, 200, 300 or 400 as speed
    return (rand() % 4 + 1) * 100;
}

int GameState::_getRandomSize()
{
    return rand() % 6 + 30;
}