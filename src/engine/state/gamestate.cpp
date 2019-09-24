#include "gamestate.h"

GameState::GameState(sf::RenderWindow *window)
{
    this->_window = window;
    this->_initGameState();
}

GameState::~GameState()
{
    for (auto it : this->_entities)
        delete it;
    delete this->_backgroundSprite;
    for (auto it : this->buttons)
        delete it.second;
    std::cout << "game state cleared\n";
}

void GameState::_loadAssets()
{
    //=====load textures=====//
    sf::Texture bg;
    bg.loadFromFile("assets/images/bg.jpg");
    this->_textures["BG"] = bg;
    sf::Texture fmq;
    fmq.loadFromFile("assets/images/fmq.png");
    this->_textures["FMQ"] = fmq;
    sf::Texture circle;
    circle.loadFromFile("assets/images/circle.png");
    this->_textures["CIRCLE"] = circle;
    sf::Texture rectangle;
    rectangle.loadFromFile("assets/images/rect.png");
    this->_textures["RECTANGLE"] = rectangle;
    sf::Texture btnStart;
    btnStart.loadFromFile("assets/images/btn_start.png");
    this->_textures["BTN_START"] = btnStart;
    sf::Texture btnCreditsIn;
    btnCreditsIn.loadFromFile("assets/images/btn_credits_in.png");
    this->_textures["BTN_CREDITS_IN"] = btnCreditsIn;
    sf::Texture btnCreditsOut;
    btnCreditsOut.loadFromFile("assets/images/btn_credits_out.png");
    this->_textures["BTN_CREDITS_OUT"] = btnCreditsOut;
    //=====load sounds=====//
    this->_backgroundMusic.openFromFile("assets/sounds/bg_music.ogg");

    sf::SoundBuffer startBuffer;
    startBuffer.loadFromFile("assets/sounds/button_press.wav");
    sf::Sound start;
    start.setBuffer(startBuffer);
    this->_sounds["START"] = start;

    sf::SoundBuffer creditsInBuffer;
    creditsInBuffer.loadFromFile("assets/sounds/credits_in.wav");
    sf::Sound creditsIn;
    creditsIn.setBuffer(creditsInBuffer);
    this->_sounds["CREDITS_IN"] = creditsIn;

    sf::SoundBuffer creditsOutBuffer;
    creditsOutBuffer.loadFromFile("assets/sounds/credits_out.wav");
    sf::Sound creditsOut;
    creditsOut.setBuffer(creditsOutBuffer);
    this->_sounds["CREDITS_OUT"] = creditsOut;
    //=====load fonts=====//
    sf::Font budmo;
    budmo.loadFromFile("assets/fonts/budmo.ttf");
    this->_fonts["BUDMO"] = budmo;
    sf::Font quentell;
    quentell.loadFromFile("assets/fonts/quentell.ttf");
    this->_fonts["QUENTELL"] = quentell;
    sf::Font vintages;
    vintages.loadFromFile("assets/fonts/vintages.ttf");
    this->_fonts["VINTAGES"] = vintages;
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
    this->_gameInProgress = false;

    this->_loadAssets();
    this->_initSprites();
    this->_initButtons();
    this->_initTexts();
    this->_initOrResetEntities();
    this->_startBackgroundMusic();
}

void GameState::_initSprites()
{
    //new background sprite
    //not defining size cause the image is exactly of the same size as window
    this->_backgroundSprite = new sf::Sprite();
    this->_backgroundSprite->setTexture(this->_textures["BG"]);
    this->_fmqLogo = new sf::Sprite();
    this->_fmqLogo->setTexture(this->_textures["FMQ"]);
    this->_fmqLogo->scale(sf::Vector2f(0.5, 0.5));
    this->_fmqLogo->setPosition(20, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + (MENU_BAR_HEIGHT / 2) - (this->_fmqLogo->getGlobalBounds().height / 2)));
}

void GameState::_initButtons()
{
    //button start
    //positioned in the center of menu bar
    this->buttons["START"] = new gui::Button((WINDOW_WIDTH / 2) - 50, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 10), new sf::CircleShape(50),
                                             sf::Color(230, 230, 230, 230),
                                             sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
                                             &this->_fonts["BUDMO"], "START", 24, &this->_textures["BTN_START"], &this->_sounds["START"]);
    this->buttons["CREDITS_IN"] = new gui::Button((WINDOW_WIDTH / 2) - 210, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25), new sf::RectangleShape(sf::Vector2f(140, 70)),
                                                  sf::Color(230, 230, 230, 230),
                                                  sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
                                                  &this->_fonts["VINTAGES"], "CREDITS IN", 20, &this->_textures["BTN_CREDITS_IN"], &this->_sounds["CREDITS_IN"]);
    this->buttons["CREDITS_OUT"] = new gui::Button((WINDOW_WIDTH / 2) + 70, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25), new sf::RectangleShape(sf::Vector2f(140, 70)),
                                                   sf::Color(230, 230, 230, 230),
                                                   sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
                                                   &this->_fonts["VINTAGES"], "CREDITS OUT", 20, &this->_textures["BTN_CREDITS_OUT"], &this->_sounds["CREDITS_OUT"]);
}

void GameState::_initTexts()
{
    this->_textNrOfCredits.setFont(this->_fonts["QUENTELL"]);
    this->_textNrOfCredits.setFillColor(sf::Color::White);
    std::stringstream text;
    text << "Current Credits: " << this->_nrOfCredits;
    this->_textNrOfCredits.setString(text.str());
    this->_textNrOfCredits.setCharacterSize(14);
    this->_textNrOfCredits.setPosition(0, 0);
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
            this->_entities.push_back(new Rectangle(640, 360, this->_getRandomSpeed(), &this->_textures["RECTANGLE"],
                                                    this->_getRandomColor(), this->_getRandomSize(), this->_getRandomSize()));
        else
            this->_entities.push_back(new Circle(640, 360, this->_getRandomSpeed(), &this->_textures["CIRCLE"],
                                                 this->_getRandomColor(), this->_getRandomSize()));
        --counter;
    }
}

void GameState::_startBackgroundMusic()
{
    //start playing the background music
    this->_backgroundMusic.play();
}

void GameState::startOrPauseGame()
{
    if (this->_animating)
        this->_animating = false;
    else if (this->_gameInProgress && !this->_animating)
        this->_animating = true;
    else if (!this->_gameInProgress && !this->_animating && this->_nrOfCredits > 0)
    {
        --this->_nrOfCredits;
        this->_gameInProgress = true;
        this->_animating = true;
    }
}

void GameState::addCredit()
{
    ++this->_nrOfCredits;
}

void GameState::removeCredits()
{
    this->_nrOfCredits = 0;
}

void GameState::update(const float &dt)
{
    //update buttons based on mouse position
    for (auto button : this->buttons)
        //check for mouse position in current window to update current button state
        button.second->update(sf::Mouse::getPosition(*this->_window));
    std::stringstream text;
    text << "Current Credits: " << this->_nrOfCredits;
    this->_textNrOfCredits.setString(text.str());

    this->_checkIfPlayFinished();

    if (this->_gameInProgress && this->_animating)
        //update each of the entities
        for (auto entity : this->_entities)
        {
            if (!entity->getHasAnimationFinished())
            {
                entity->move(dt);
                entity->update(dt);
            }
        }
}

void GameState::_checkIfPlayFinished()
{
    //checks if all entities have finished their animation
    if (std::all_of(this->_entities.begin(), this->_entities.end(), [](Entity *e) { return e->getHasAnimationFinished(); }))
    {
        this->_animating = false;
        this->_gameInProgress = false;
        this->_initOrResetEntities();
        std::cout << "game ended\n";
    }
}

void GameState::render(sf::RenderTarget *target)
{
    //draw the background
    if (this->_backgroundSprite)
        target->draw(*this->_backgroundSprite);
    //draw the logo
    if (this->_fmqLogo)
        target->draw(*this->_fmqLogo);
    //draw each of the buttons
    for (auto button : this->buttons)
        button.second->render(target);
    target->draw(this->_textNrOfCredits);
    //render each of the entities
    for (auto entity : this->_entities)
        entity->render(target);
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