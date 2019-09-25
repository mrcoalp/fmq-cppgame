#ifndef GUI_H
#define GUI_H

#include "../headers/sfml.h"

enum EButtonState { IDLE = 0, HOVER, ACTIVE };

namespace gui {
class Button {
   public:
    Button(float x, float y, sf::Shape* shape, sf::Color idleColor,
           sf::Color hoverColor, sf::Color activeColor, sf::Font* font,
           std::string text, unsigned fontSize, sf::Texture* texture);
    virtual ~Button();

    /**
     * Check if button is pressed
     */
    const bool isPressed() const;

    /**
     * Update button based on mouse position passed as reference
     */
    void update(const sf::Vector2i& mousePosition);
    void render(sf::RenderTarget* target = NULL);

   private:
    sf::Color _idleColor;
    sf::Color _hoverColor;
    sf::Color _activeColor;
    sf::Text _text;
    sf::Shape* _shape;
    short unsigned _buttonState;
};
}   // namespace gui

#endif   // GUI_H
