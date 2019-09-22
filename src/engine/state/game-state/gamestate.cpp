#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window) : State(window)
{
    //set seed for random generator
    //prevents sequence of same numbers over and over
    srand(time(NULL));
    this->initGameState();
}

GameState::~GameState()
{
    for (std::vector<Entity *>::iterator i = this->_entities.begin(); i != this->_entities.end(); ++i)
        delete (*i);

    std::cout << "gamestate cleared\n";
}

void GameState::initGameState()
{
    int counter = 50;
    while (counter > 0)
    {
        if (counter < 25)
            this->_entities.push_back(new Circle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize()));
        else
            this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
        --counter;
    }
    this->_entities.push_back(new Texture(640, 360, this->_getRandomSpeed(), this->_getRandomColor()));
}

void GameState::updateKeybinds(const float &dt)
{
    this->checkForQuit();
}

void GameState::update(const float &dt)
{
    this->updateKeybinds(dt);

    for (size_t i = 0; i < this->_entities.size(); i++)
        this->_entities[i]->update(dt);
}

void GameState::render(sf::RenderTarget *target)
{
    for (size_t i = 0; i < this->_entities.size(); i++)
        this->_entities[i]->render(target);
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