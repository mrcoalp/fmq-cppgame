#include "entity.h"

Entity::Entity(int x, int y, int speed, sf::Texture* texture) {
    _shape = NULL;
    _movement = NULL;
    _texture = texture;
    _hasAnimationFinished = false;
    _direction_x = _getRandomDirection();
    _direction_y = _getRandomDirection();
}

Entity::~Entity() { delete _movement; }

void Entity::move(const float& dt) {
    // movement component updates entity position
    _movement->move(_direction_x, _direction_y, dt);
}

void Entity::update(const float& dt) {
    _movement->update(dt);  // move
    animate();              // animate
    // when entity collides with window border, animation finishes
    if (_checkCollision()) _hasAnimationFinished = true;
}

void Entity::render(sf::RenderTarget* target) {
    // draws shape in render target
    // passed as argument from gamestate
    target->draw(*_shape);
}

void Entity::_createMovement(const float speed) { _movement = new MovementComponent(speed, _shape); }

bool Entity::_checkCollision() {
    // define hitbox
    // TODO(marco): maybe as a property?
    std::map<std::string, float> hitbox;
    hitbox["LEFT"] = _shape->getGlobalBounds().left;
    hitbox["RIGHT"] = _shape->getGlobalBounds().left + _shape->getGlobalBounds().width;
    hitbox["UP"] = _shape->getGlobalBounds().top;
    hitbox["DOWN"] = _shape->getGlobalBounds().top + _shape->getGlobalBounds().height;
    // checks if entity hitbox collides with window border and/or menu
    return !(hitbox["LEFT"] > 0 && hitbox["RIGHT"] < WINDOW_WIDTH && hitbox["UP"] > 0 && hitbox["DOWN"] < WINDOW_HEIGHT - MENU_BAR_HEIGHT);
}

float Entity::_getRandomDirection() {
    float diff = 1.0 - 0.3;  // define difference between min and max values possible
    // return a float between 0.3 and 1 multiplied either by -1 or 1
    // this ensures that the movement is never 'too slow'
    return (((static_cast<float>(rand()) / RAND_MAX) * diff) + 0.3) * (rand() % 2 == 0 ? 1 : -1);
}

const bool& Entity::getHasAnimationFinished() const { return _hasAnimationFinished; }