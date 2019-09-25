#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "../constants.h"
#include "../engine/movement/movementcomponent.h"
#include "../headers/sfml.h"

class Entity {
   public:
    Entity(int x, int y, int speed, sf::Texture* texture);
    virtual ~Entity();

    /**
     * Getter of the state of animation
     */
    virtual const bool& getHasAnimationFinished() const;

    /**
     * Updates entity position
     * Treated in movement component
     */
    virtual void move(const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = NULL);
    /**
     * Animates object
     * Method to be implemented in child classes
     * Each one has a different animation
     */
    virtual void animate() = 0;   // pure virtual

   protected:
    sf::Shape* _shape;
    sf::Texture* _texture;
    MovementComponent* _movement;

    /**
     * Creates a new movement component
     */
    void _createMovement(const float speed);

   private:
    float _direction_x;
    float _direction_y;
    bool _hasAnimationFinished;

    /**
     * Checks entity collision with window boundaries and/or menu
     */
    bool _checkCollision();
    /**
     * Returns a random float between [-1, -0.3] and [0.3, 1]
     */
    float _getRandomDirection();
};

#endif   // ENTITY_H
