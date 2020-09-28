#include "game.h"

Game::Game() {
    // setup window and state
    _setupWindow();
    _setupState();
}

Game::~Game() {
    delete _window;
    delete _state;
}

void Game::_setupWindow() {
    // new window
    // sf::Style::Close disables resizing of the window
    // TODO(marco): maybe enable resize later if there is time...
    _window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FMQ", sf::Style::Close);
}

void Game::_setupState() { _state = new GameState(_window); }

void Game::_checkSFMLEvents() {
    while (_window->pollEvent(_sfEvent)) {
        // close window when 'X' is pressed
        if (_sfEvent.type == sf::Event::Closed) _window->close();
        // check for keyboard input
        if (_sfEvent.type == sf::Event::KeyPressed) _checkKeyboardActions();
        // check for mouse button press
        if (_sfEvent.type == sf::Event::MouseButtonPressed)
            if (_sfEvent.mouseButton.button == sf::Mouse::Left) _checkMouseActions();
    }
}

void Game::_checkKeyboardActions() {
    if (_sfEvent.key.code == sf::Keyboard::Space) _state->startOrPauseGame();
    if (_sfEvent.key.code == sf::Keyboard::I) _state->addCredit();
    if (_sfEvent.key.code == sf::Keyboard::O) _state->removeCredits();
}

void Game::_checkMouseActions() {
    if (_state->buttons["START"]->isPressed()) _state->startOrPauseGame();
    if (_state->buttons["CREDITS_IN"]->isPressed()) _state->addCredit();
    if (_state->buttons["CREDITS_OUT"]->isPressed()) _state->removeCredits();
}

void Game::_updateDeltaTime() {
    // updates dt with the time it takes to update and render one frame
    _dt = _dtClock.restart().asSeconds();
}

void Game::_update() {
    _updateDeltaTime();
    _state->update(_dt);
    _checkSFMLEvents();
}

void Game::_render() {
    _window->clear();
    _state->render(_window);
    _window->display();
}

void Game::run() {
    // sets the maximum framerate
    _window->setFramerateLimit(60);
    // prevents repetition of key strokes
    // we only have single event actions, not repetitive ones like
    // player movement
    _window->setKeyRepeatEnabled(false);
    // while window is open run the game
    // updates state and renders objects
    while (_window->isOpen()) {
        _update();
        _render();
    }
}