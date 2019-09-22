#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window)
{
    srand(time(NULL));
    std::cout << "gamestate init\n";
    this->_window = window;
    this->_quit = false;
    this->_nrOfCredits = 0;
    this->_animating = false;
    // this->_initGameState();
}

GameState::~GameState()
{
    for (std::vector<Entity *>::iterator i = this->_entities.begin(); i != this->_entities.end(); ++i)
        delete *i;
    std::cout << "game state cleared\n";
}

void GameState::_initGameState()
{
    // this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));

    int counter = 100;
    while (counter > 0)
    {
        if (counter < 25)
            this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
        else if (counter < 100)
            this->_entities.push_back(new Circle(640, 360, this->_getRandomSpeed(), this->_getRandomColor(), this->_getRandomSize()));
        --counter;
    }
}

const bool &GameState::getQuit() const
{
    return this->_quit;
}

void GameState::startGame()
{
    this->_initGameState();
}

void GameState::update(const float &dt)
{
    for (size_t i = 0; i < this->_entities.size(); i++)
    {
        if (!this->_entities[i]->getHasAnimationFinished())
        {
            this->_entities[i]->move(dt);
            this->_entities[i]->update(dt);
        }
    }
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
    switch (rand() % 4)
    {
    case 0:
        return 50;
    case 1:
        return 100;
    case 2:
        return 150;
    case 3:
        return 200;
    default:
        return 0;
    }
}

int GameState::_getRandomSize()
{
    switch (rand() % 4)
    {
    case 0:
        return 20;
    case 1:
        return 30;
    case 2:
        return 40;
    case 3:
        return 50;
    default:
        return 0;
    }
}