#include "gui.h"
#include <iostream>
gui::Button::Button(float x, float y, sf::Shape* shape, sf::Color idleColor,
                    sf::Color hoverColor, sf::Color activeColor, sf::Font* font,
                    std::string text, unsigned fontSize, sf::Texture* texture) {
    this->_buttonState = IDLE;   // starts as idle
    //====setting the shape and colors====//
    this->_shape = shape;
    this->_shape->setPosition(x, y);
    this->_idleColor = idleColor;
    this->_hoverColor = hoverColor;
    this->_activeColor = activeColor;
    this->_shape->setFillColor(this->_idleColor);
    this->_shape->setTexture(texture);
    //====setting the text====//
    this->_text.setFont(*font);
    this->_text.setString(text);
    this->_text.setFillColor(sf::Color::White);
    this->_text.setCharacterSize(fontSize);
    this->_text.setPosition(
        this->_shape->getPosition().x +
            (this->_shape->getGlobalBounds().width / 2) -
            (this->_text.getGlobalBounds().width / 2),
        this->_shape->getPosition().y +
            (this->_shape->getGlobalBounds().height / 2) -
            (this->_text.getGlobalBounds()
                 .height));   // set text in the center of the shape
}

gui::Button::~Button() { delete this->_shape; }

const bool gui::Button::isPressed() const {
    if (this->_buttonState == ACTIVE) return true;
    return false;
}

void gui::Button::update(const sf::Vector2i& mousePosition) {
    this->_buttonState = IDLE;   // make button idle if not hover or active
    // if mouse position is inside the bounds of button check for click or not
    if (this->_shape->getGlobalBounds().contains(
            static_cast<sf::Vector2f>(mousePosition))) {
        this->_buttonState = HOVER;   // set to hover

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->_buttonState = ACTIVE;   // set to active on mouse click
        }
    }

    switch (this->_buttonState) {   // change color based on current state
        case IDLE:
            this->_shape->setFillColor(this->_idleColor);
            break;
        case HOVER:
            this->_shape->setFillColor(this->_hoverColor);
            break;
        case ACTIVE:
            this->_shape->setFillColor(this->_activeColor);
            break;
        default:
            this->_shape->setFillColor(sf::Color::Black);
            break;
    }
}

void gui::Button::render(sf::RenderTarget* target) {
    target->draw(*this->_shape);   // render shape
    target->draw(this->_text);     // render text
}