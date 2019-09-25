#include "gamestate.h"

GameState::GameState(sf::RenderWindow* window) {
    this->_window = window;
    this->_initGameState();
}

GameState::~GameState() {
    for (auto it : this->_entities) delete it;
    for (auto it : this->_sprites) delete it.second;
    for (auto it : this->buttons) delete it.second;
}

void GameState::_initGameState() {
    // provide a seed to rand function
    srand(time(NULL));
    // the game starts with 0 credits
    // player must insert credits first to play
    this->_nrOfCredits = 0;
    this->_totalInCredits = 0;
    this->_totalOutCredits = 0;
    this->_nrOfPlays = 0;
    // animation only starts after player input
    this->_gameInProgress = false;
    this->_animating = false;

    this->_loadAssets();
    this->_initSprites();
    this->_initButtons();
    this->_initTexts();
    this->_initOrResetEntities();
    this->_startBackgroundMusic();
}

void GameState::_loadAssets() {
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

void GameState::_initSprites() {
    // new background sprite
    // not defining size cause the image is exactly of the same size as window
    this->_sprites["BG"] = new sf::Sprite();
    this->_sprites["BG"]->setTexture(this->_textures["BG"]);
    this->_sprites["FMQ"] = new sf::Sprite();
    this->_sprites["FMQ"]->setTexture(this->_textures["FMQ"]);
    this->_sprites["FMQ"]->scale(sf::Vector2f(0.5, 0.5));
    this->_sprites["FMQ"]->setPosition(
        20, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + (MENU_BAR_HEIGHT / 2) -
             (this->_sprites["FMQ"]->getGlobalBounds().height / 2)));
}

void GameState::_initButtons() {
    // button start
    // positioned in the center of menu bar
    this->buttons["START"] = new gui::Button(
        (WINDOW_WIDTH / 2) - 50, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 10),
        new sf::CircleShape(50), sf::Color(230, 230, 230, 230),
        sf::Color(255, 255, 255, 255), sf::Color(200, 200, 200, 200),
        &this->_fonts["BUDMO"], "START", 24, &this->_textures["BTN_START"]);

    this->buttons["CREDITS_IN"] = new gui::Button(
        (WINDOW_WIDTH / 2) - 210, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25),
        new sf::RectangleShape(sf::Vector2f(140, 70)),
        sf::Color(230, 230, 230, 230), sf::Color(255, 255, 255, 255),
        sf::Color(200, 200, 200, 200), &this->_fonts["VINTAGES"], "CREDITS IN",
        20, &this->_textures["BTN_CREDITS_IN"]);

    this->buttons["CREDITS_OUT"] = new gui::Button(
        (WINDOW_WIDTH / 2) + 70, (WINDOW_HEIGHT - MENU_BAR_HEIGHT + 25),
        new sf::RectangleShape(sf::Vector2f(140, 70)),
        sf::Color(230, 230, 230, 230), sf::Color(255, 255, 255, 255),
        sf::Color(200, 200, 200, 200), &this->_fonts["VINTAGES"], "CREDITS OUT",
        20, &this->_textures["BTN_CREDITS_OUT"]);
}

void GameState::_initTexts() {
    sf::Text message;   // message for user
    message.setFont(this->_fonts["QUENTELL"]);
    message.setFillColor(sf::Color::White);
    message.setCharacterSize(24);
    message.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 200);
    this->_texts["MESSAGE"] = message;

    sf::Text nrOfCredits;
    nrOfCredits.setFont(this->_fonts["QUENTELL"]);
    nrOfCredits.setFillColor(sf::Color::White);
    nrOfCredits.setCharacterSize(18);
    nrOfCredits.setPosition(200, WINDOW_HEIGHT - MENU_BAR_HEIGHT + 20);
    this->_texts["NR_OF_CREDITS"] = nrOfCredits;

    sf::Text nrOfPlays;
    nrOfPlays.setFont(this->_fonts["QUENTELL"]);
    nrOfPlays.setFillColor(sf::Color::White);
    nrOfPlays.setCharacterSize(18);
    nrOfPlays.setPosition(200, WINDOW_HEIGHT - 40);
    this->_texts["NR_OF_PLAYS"] = nrOfPlays;

    sf::Text totalInCredits;
    totalInCredits.setFont(this->_fonts["QUENTELL"]);
    totalInCredits.setFillColor(sf::Color::White);
    totalInCredits.setCharacterSize(18);
    totalInCredits.setPosition(950, WINDOW_HEIGHT - MENU_BAR_HEIGHT + 20);
    this->_texts["TOTAL_IN_CREDITS"] = totalInCredits;

    sf::Text totalOutCredits;
    totalOutCredits.setFont(this->_fonts["QUENTELL"]);
    totalOutCredits.setFillColor(sf::Color::White);
    totalOutCredits.setCharacterSize(18);
    totalOutCredits.setPosition(950, WINDOW_HEIGHT - 40);
    this->_texts["TOTAL_OUT_CREDITS"] = totalOutCredits;
}

void GameState::_updateTexts() {
    // present instructions to user
    if (!this->_gameInProgress && this->_nrOfCredits == 0)
        this->_texts["MESSAGE"].setString(
            "Insert credits (I) to play (SPACE)\nYou can also remove all "
            "credits (O)");
    else
        this->_texts["MESSAGE"].setString("");

    std::stringstream text;

    text << "Current Credits:  " << this->_nrOfCredits;
    this->_texts["NR_OF_CREDITS"].setString(text.str());
    text.str("");   // clear string stream

    text << "Number Of Plays:  " << this->_nrOfPlays;
    this->_texts["NR_OF_PLAYS"].setString(text.str());
    text.str("");

    text << "Total Credits Inserted:  " << this->_totalInCredits;
    this->_texts["TOTAL_IN_CREDITS"].setString(text.str());
    text.str("");

    text << "Total Credits Removed:  " << this->_totalOutCredits;
    this->_texts["TOTAL_OUT_CREDITS"].setString(text.str());
    text.str("");
}

void GameState::_initOrResetEntities() {
    // delete pointers in array to prevent memory leak
    for (std::vector<Entity*>::iterator i = this->_entities.begin();
         i != this->_entities.end(); ++i)
        delete *i;
    // when game is being reset, clear vector to add new entities
    this->_entities.clear();
    // add 50 circles and 50 rectangles to entity vector with random values
    int counter = 100;
    while (counter > 0) {
        if (counter < 50)
            this->_entities.push_back(new Rectangle(
                WINDOW_WIDTH / 2, (WINDOW_HEIGHT - MENU_BAR_HEIGHT) / 2,
                this->_getRandomSpeed(), &this->_textures["RECTANGLE"],
                this->_getRandomColor(), this->_getRandomSize(),
                this->_getRandomSize()));
        else
            this->_entities.push_back(new Circle(
                WINDOW_WIDTH / 2, (WINDOW_HEIGHT - MENU_BAR_HEIGHT) / 2,
                this->_getRandomSpeed(), &this->_textures["CIRCLE"],
                this->_getRandomColor(), this->_getRandomSize()));
        --counter;
    }
}

void GameState::_startBackgroundMusic() {
    // start playing the background music
    this->_backgroundMusic.play();
}

void GameState::startOrPauseGame() {
    if (this->_animating)
        this->_animating = false;
    else if (this->_gameInProgress && !this->_animating)
        this->_animating = true;
    else if (!this->_gameInProgress && !this->_animating &&
             this->_nrOfCredits > 0) {
        --this->_nrOfCredits;
        ++this->_totalOutCredits;
        this->_gameInProgress = true;
        this->_animating = true;
    }
}

void GameState::addCredit() {
    // add a credit to current and total nr of credits
    ++this->_nrOfCredits;
    ++this->_totalInCredits;
}

void GameState::removeCredits() {
    // adds current nr of credits to total out
    this->_totalOutCredits += this->_nrOfCredits;
    // resets current nr of credits
    this->_nrOfCredits = 0;
}

void GameState::update(const float& dt) {
    // update buttons based on mouse position
    for (auto button : this->buttons)
        // check for mouse position in current window to update current button
        // state
        button.second->update(sf::Mouse::getPosition(*this->_window));

    this->_updateTexts();   // updates texts

    this->_checkIfPlayFinished();   // check for play state

    if (this->_gameInProgress && this->_animating)
        // update each of the entities
        for (auto entity : this->_entities) {
            // don't move entities that have finished it's animation
            if (!entity->getHasAnimationFinished()) {
                entity->move(dt);
                entity->update(dt);
            }
        }
}

void GameState::_checkIfPlayFinished() {
    // checks if all entities have finished their animation
    if (std::all_of(this->_entities.begin(), this->_entities.end(),
                    [](Entity* e) { return e->getHasAnimationFinished(); })) {
        this->_animating = false;
        this->_gameInProgress = false;
        ++this->_nrOfPlays;
        this->_initOrResetEntities();
    }
}

void GameState::render(sf::RenderTarget* target) {
    for (auto sprite : this->_sprites)   // draw each of the sprites
        if (sprite.second) target->draw(*sprite.second);
    // draw each of the buttons
    for (auto button : this->buttons) button.second->render(target);
    for (auto text : this->_texts) target->draw(text.second);
    // render each of the entities
    for (auto entity : this->_entities) entity->render(target);
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