#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window) : State(window)
{
    this->initGameState();
}

GameState::~GameState()
{
    for (size_t i = 0; i < this->_entities.size(); i++)
    {
        delete this->_entities[i];
    }
}

void GameState::initGameState()
{
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("/home/marco/Development/fmq-cppgame/src/assets/fmq.png");
    texture->setSmooth(true);
    this->_entities.push_back(new Texture(640, 360, this->_getRandomSpeed(), texture));

    for (size_t i = 0; i < 75; i++)
    {
        if (i < 25)
            this->_entities.push_back(new Circle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize()));
        else if (i < 50)
            this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
    }
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
    return (rand() % 5) * 100 + 100;
}

int GameState::_getRandomSize()
{
    return rand() % 6 + 30;
}