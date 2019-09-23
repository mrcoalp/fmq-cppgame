#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window)
{
    this->_window = window;
    this->_initGameState();
}

GameState::~GameState()
{
    for (std::vector<Entity *>::iterator i = this->_entities.begin(); i != this->_entities.end(); ++i)
        delete *i;
    delete this->_backgroundSprite;
    std::cout << "game state cleared\n";
}

void GameState::_loadAssets()
{
    //=====load textures=====//
    sf::Texture bg;
    bg.loadFromFile("assets/images/bg.jpg");
    this->_textures["BG"] = bg;
    sf::Texture circle;
    circle.loadFromFile("assets/images/circle_2.png");
    this->_textures["CIRCLE"] = circle;
    sf::Texture rectangle;
    rectangle.loadFromFile("assets/images/rectangle.jpeg");
    this->_textures["RECTANGLE"] = rectangle;
    //=====load sounds=====//
    this->_backgroundMusic.openFromFile("assets/sounds/bg_music.ogg");
}

void GameState::_initGameState()
{
    //provide a seed to rand function
    srand(time(NULL));
    //inti bacgroundImage pointer as NULL
    this->_backgroundSprite = NULL;
    //the game starts with 0 credits
    //player must insert credits first to play
    this->_nrOfCredits = 0;
    //animation only starts after player input
    this->_animating = false;

    this->_loadAssets();
    this->_initSprites();
    this->_initOrResetEntities();
    this->_startBackgroundMusic();
}

void GameState::_initSprites()
{
    //new background sprite
    //not defining size cause the image is exactly of the same size as window
    this->_backgroundSprite = new sf::Sprite();
    this->_backgroundSprite->setTexture(this->_textures["BG"]);
}

void GameState::_initOrResetEntities()
{
    //delete pointers in array to prevent memory leak
    for (std::vector<Entity *>::iterator i = this->_entities.begin(); i != this->_entities.end(); ++i)
        delete *i;
    //when game is being reset, clear vector to add new entities
    this->_entities.clear();
    //add 50 circles and 50 rectangles to entity vector with random values
    int counter = 100;
    while (counter > 0)
    {
        if (counter < 50)
            this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), &this->_textures["RECTANGLE"], this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
        else
            this->_entities.push_back(new Circle(640, 360, this->_getRandomSpeed(), &this->_textures["CIRCLE"], this->_getRandomColor(), this->_getRandomSize()));
        --counter;
    }
}

void GameState::_startBackgroundMusic()
{
    //start playing the background music
    this->_backgroundMusic.play();
}

void GameState::startGame()
{
}

void GameState::setAnimating()
{
    this->_animating = !this->_animating;
}

void GameState::addCredit()
{
    this->_nrOfCredits++;
}

void GameState::update(const float &dt)
{
    if (this->_animating && this->_nrOfCredits > 0)
        //update each of the entities
        for (size_t i = 0; i < this->_entities.size(); i++)
        {
            if (!this->_entities[i]->getHasAnimationFinished())
            {
                this->_entities[i]->move(dt);
                this->_entities[i]->update(dt);
            }
        }
    //checks if all entities have finished their animation
    if (std::all_of(this->_entities.begin(), this->_entities.end(), [](Entity *e) { return e->getHasAnimationFinished(); }))
    {
        this->_animating = false;
        this->_initOrResetEntities();
        std::cout << "game ended\n";
    }
}

void GameState::render(sf::RenderTarget *target)
{
    //draw the background
    if (this->_backgroundSprite)
        target->draw(*this->_backgroundSprite);
    //render each of the entities
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
        return sf::Color::Cyan;
    default:
        return sf::Color::White;
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