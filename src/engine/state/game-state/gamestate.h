#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../state.h"
#include "../../../entities/entity.h"
#include "../../../entities/shapes/circle/circle.h"
#include "../../../entities/shapes/rectangle/rectangle.h"
#include "../../../entities/texture/texture.h"

#include <vector>

class GameState : public State
{
public:
    GameState(sf::RenderWindow *window);
    ~GameState();

    void initGameState();
    void updateKeybinds(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = NULL);

protected:
private:
    std::vector<Entity *> _entities;

    sf::Color _getRandomColor();
    int _getRandomSpeed();
    int _getRandomSize();
};

#endif // GAMESTATE_H
