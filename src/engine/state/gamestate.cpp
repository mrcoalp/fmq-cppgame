#include "gamestate.h"

GameState::GameState(sf::RenderWindow* window) {
    _window = window;
    _initGameState();
}

GameState::~GameState() {
    for (auto it : _entities) delete it;
    for (auto it : _sprites) delete it.second;
    for (auto it : buttons) delete it.second;
}

void GameState::_initGameState() {
    // provide a seed to rand function
    srand(time(NULL));
    // the game starts with 0 credits
    // player must insert credits first to play
    _nrOfCredits = 0;
    _totalInCredits = 0;
    _totalOutCredits = 0;
    _nrOfPlays = 0;
    // animation only starts after player input
    _gameInProgress = false;
    _animating = false;

    _loadAssets();
    _initSprites();
    _initButtons();
    _initTexts();
    _initOrResetEntities();
    _startBackgroundMusic();
}

void GameState::_loadAssets() {
    //=====load textures=====//
    sf::Texture bg;
    bg.loadFromFile("assets/images/bg.jpg");
    _textures["BG"] = bg;
    sf::Texture fmq;
    fmq.loadFromFile("assets/images/fmq.png");
    _textures["FMQ"] = fmq;
    sf::Texture circle;
    circle.loadFromFile("assets/images/circle.png");
    _textures["CIRCLE"] = circle;
    sf::Texture rectangle;
    rectangle.loadFromFile("assets/images/rect.png");
    _textures["RECTANGLE"] = rectangle;
    sf::Texture btnStart;
    btnStart.loadFromFile("assets/images/btn_start.png");
    _textures["BTN_START"] = btnStart;
    sf::Texture btnCreditsIn;
    btnCreditsIn.loadFromFile("assets/images/btn_credits_in.png");
    _textures["BTN_CREDITS_IN"] = btnCreditsIn;
    sf::Texture btnCreditsOut;
    btnCreditsOut.loadFromFile("assets/images/btn_credits_out.png");
    _textures["BTN_CREDITS_OUT"] = btnCreditsOut;
    //=====load sounds=====//
    _backgroundMusic.openFromFile("assets/sounds/bg_music.ogg");
    //=====load fonts=====//
    sf::Font budmo;
    budmo.loadFromFile("assets/fonts/budmo.ttf");
    _fonts["BUDMO"] = budmo;
    sf::Font quentell;
    quentell.loadFromFile("assets/fonts/quentell.ttf");
    _fonts["QUENTELL"] = quentell;
    sf::Font vintages;
    vintages.loadFromFile("assets/fonts/vintages.ttf");
    _fonts["VINTAGES"] = vintages;
}

void GameState::_initSprites() {
    // new background sprite
    // not defining size cause the image is exactly of the same size as window
    _sprites["BG"] = new sf::Sprite();
    _sprites["BG"]->setTexture(_textures["BG"]);
    _sprites["FMQ"] = new sf::Sprite();
    _sprites["FMQ"]->setTexture(_textures["FMQ"]);
    _sprites["FMQ"]->scale(sf::Vector2f(0.5, 0.5));
    _sprites["FMQ"]->setPosition(20, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + (MENU_BAR_HEIGHT / 2) - (_sprites["FMQ"]->getGlobalBounds().height / 2)));
}

void GameState::_initButtons() {
    // button start
    // positioned in the center of menu bar
    buttons["START"] =
        new gui::Button((WINDOW_WIDTH / 2) - 50, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 10), new sf::CircleShape(50), sf::Color(230, 230, 230, 230),
                        sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200), &_fonts["BUDMO"], "START", 24, &_textures["BTN_START"]);

    buttons["CREDITS_IN"] =
        new gui::Button((WINDOW_WIDTH / 2) - 210, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25), new sf::RectangleShape(sf::Vector2f(140, 70)),
                        sf::Color(230, 230, 230, 230), sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200), &_fonts["VINTAGES"],
                        "CREDITS IN", 20, &_textures["BTN_CREDITS_IN"]);

    buttons["CREDITS_OUT"] = new gui::Button(
        (WINDOW_WIDTH / 2) + 70, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25), new sf::RectangleShape(sf::Vector2f(140, 70)), sf::Color(230, 230, 230, 230),
        sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200), &_fonts["VINTAGES"], "CREDITS OUT", 20, &_textures["BTN_CREDITS_OUT"]);
}

void GameState::_initTexts() {
    sf::Text message;  // message for user
    message.setFont(_fonts["QUENTELL"]);
    message.setFillColor(sf::Color::White);
    message.setCharacterSize(24);
    message.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 200);
    _texts["MESSAGE"] = message;

    sf::Text nrOfCredits;
    nrOfCredits.setFont(_fonts["QUENTELL"]);
    nrOfCredits.setFillColor(sf::Color::White);
    nrOfCredits.setCharacterSize(18);
    nrOfCredits.setPosition(200, WINDOW_HEIGHT - MENU_BAR_HEIGHT + 20);
    _texts["NR_OF_CREDITS"] = nrOfCredits;

    sf::Text nrOfPlays;
    nrOfPlays.setFont(_fonts["QUENTELL"]);
    nrOfPlays.setFillColor(sf::Color::White);
    nrOfPlays.setCharacterSize(18);
    nrOfPlays.setPosition(200, WINDOW_HEIGHT - 40);
    _texts["NR_OF_PLAYS"] = nrOfPlays;

    sf::Text totalInCredits;
    totalInCredits.setFont(_fonts["QUENTELL"]);
    totalInCredits.setFillColor(sf::Color::White);
    totalInCredits.setCharacterSize(18);
    totalInCredits.setPosition(950, WINDOW_HEIGHT - MENU_BAR_HEIGHT + 20);
    _texts["TOTAL_IN_CREDITS"] = totalInCredits;

    sf::Text totalOutCredits;
    totalOutCredits.setFont(_fonts["QUENTELL"]);
    totalOutCredits.setFillColor(sf::Color::White);
    totalOutCredits.setCharacterSize(18);
    totalOutCredits.setPosition(950, WINDOW_HEIGHT - 40);
    _texts["TOTAL_OUT_CREDITS"] = totalOutCredits;
}

void GameState::_updateTexts() {
    // present instructions to user
    if (!_gameInProgress && _nrOfCredits == 0)
        _texts["MESSAGE"].setString(
            "Insert credits (I) to play (SPACE)\nYou can also remove all "
            "credits (O)");
    else
        _texts["MESSAGE"].setString("");

    std::stringstream text;

    text << "Current Credits:  " << _nrOfCredits;
    _texts["NR_OF_CREDITS"].setString(text.str());
    text.str("");  // clear string stream

    text << "Number Of Plays:  " << _nrOfPlays;
    _texts["NR_OF_PLAYS"].setString(text.str());
    text.str("");

    text << "Total Credits Inserted:  " << _totalInCredits;
    _texts["TOTAL_IN_CREDITS"].setString(text.str());
    text.str("");

    text << "Total Credits Removed:  " << _totalOutCredits;
    _texts["TOTAL_OUT_CREDITS"].setString(text.str());
    text.str("");
}

void GameState::_initOrResetEntities() {
    // delete pointers in array to prevent memory leak
    for (std::vector<Entity*>::iterator i = _entities.begin(); i != _entities.end(); ++i) delete *i;
    // when game is being reset, clear vector to add new entities
    _entities.clear();
    // add 50 circles and 50 rectangles to entity vector with random values
    int counter = 100;
    while (counter > 0) {
        if (counter < 50)
            _entities.push_back(new Rectangle(WINDOW_WIDTH / 2, (WINDOW_HEIGHT - MENU_BAR_HEIGHT) / 2, _getRandomSpeed(), &_textures["RECTANGLE"],
                                              _getRandomColor(), _getRandomSize(), _getRandomSize()));
        else
            _entities.push_back(new Circle(WINDOW_WIDTH / 2, (WINDOW_HEIGHT - MENU_BAR_HEIGHT) / 2, _getRandomSpeed(), &_textures["CIRCLE"],
                                           _getRandomColor(), _getRandomSize()));
        --counter;
    }
}

void GameState::_startBackgroundMusic() {
    // start playing the background music
    _backgroundMusic.play();
}

void GameState::startOrPauseGame() {
    if (_animating)
        _animating = false;
    else if (_gameInProgress && !_animating)
        _animating = true;
    else if (!_gameInProgress && !_animating && _nrOfCredits > 0) {
        --_nrOfCredits;
        ++_totalOutCredits;
        _gameInProgress = true;
        _animating = true;
    }
}

void GameState::addCredit() {
    // add a credit to current and total nr of credits
    ++_nrOfCredits;
    ++_totalInCredits;
}

void GameState::removeCredits() {
    // adds current nr of credits to total out
    _totalOutCredits += _nrOfCredits;
    // resets current nr of credits
    _nrOfCredits = 0;
}

void GameState::update(const float& dt) {
    // update buttons based on mouse position
    for (auto button : buttons)
        // check for mouse position in current window to update current button
        // state
        button.second->update(sf::Mouse::getPosition(*_window));

    _updateTexts();  // updates texts

    _checkIfPlayFinished();  // check for play state

    if (_gameInProgress && _animating)
        // update each of the entities
        for (auto entity : _entities) {
            // don't move entities that have finished it's animation
            if (!entity->getHasAnimationFinished()) {
                entity->move(dt);
                entity->update(dt);
            }
        }
}

void GameState::_checkIfPlayFinished() {
    // checks if all entities have finished their animation
    if (std::all_of(_entities.begin(), _entities.end(), [](Entity* e) { return e->getHasAnimationFinished(); })) {
        _animating = false;
        _gameInProgress = false;
        ++_nrOfPlays;
        _initOrResetEntities();
    }
}

void GameState::render(sf::RenderTarget* target) {
    for (auto sprite : _sprites)  // draw each of the sprites
        if (sprite.second) target->draw(*sprite.second);
    // draw each of the buttons
    for (auto button : buttons) button.second->render(target);
    for (auto text : _texts) target->draw(text.second);
    // render each of the entities
    for (auto entity : _entities) entity->render(target);
}

sf::Color GameState::_getRandomColor() {
    switch (rand() % 5) {
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

int GameState::_getRandomSpeed() {
    switch (rand() % 4) {
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

int GameState::_getRandomSize() {
    switch (rand() % 4) {
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