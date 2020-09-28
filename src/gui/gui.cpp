#include "gui.h"

gui::Button::Button(float x, float y, sf::Shape* shape, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Font* font,
                    std::string text, unsigned fontSize, sf::Texture* texture) {
    _buttonState = IDLE;  // starts as idle
    //====setting the shape and colors====//
    _shape = shape;
    _shape->setPosition(x, y);
    _idleColor = idleColor;
    _hoverColor = hoverColor;
    _activeColor = activeColor;
    _shape->setFillColor(_idleColor);
    _shape->setTexture(texture);
    //====setting the text====//
    _text.setFont(*font);
    _text.setString(text);
    _text.setFillColor(sf::Color::White);
    _text.setCharacterSize(fontSize);
    _text.setPosition(
        _shape->getPosition().x + (_shape->getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2),
        _shape->getPosition().y + (_shape->getGlobalBounds().height / 2) - (_text.getGlobalBounds().height));  // set text in the center of the shape
}

gui::Button::~Button() { delete _shape; }

const bool gui::Button::isPressed() const {
    if (_buttonState == ACTIVE) return true;
    return false;
}

void gui::Button::update(const sf::Vector2i& mousePosition) {
    _buttonState = IDLE;  // make button idle if not hover or active
    // if mouse position is inside the bounds of button check for click or not
    if (_shape->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
        _buttonState = HOVER;  // set to hover

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _buttonState = ACTIVE;  // set to active on mouse click
        }
    }

    switch (_buttonState) {  // change color based on current state
        case IDLE:
            _shape->setFillColor(_idleColor);
            break;
        case HOVER:
            _shape->setFillColor(_hoverColor);
            break;
        case ACTIVE:
            _shape->setFillColor(_activeColor);
            break;
        default:
            _shape->setFillColor(sf::Color::Black);
            break;
    }
}

void gui::Button::render(sf::RenderTarget* target) {
    target->draw(*_shape);  // render shape
    target->draw(_text);    // render text
}