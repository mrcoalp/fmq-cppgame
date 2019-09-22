#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../state.h"
#include "../../../entities/entity.h"
#include "../../../entities/shapes/circle/circle.h"
#include "../../../entities/shapes/rectangle/rectangle.h"
#include "../../../entities/texture/texture.h"

#include <vector>

class MenuState : public State
{
public:
    MenuState(sf::RenderWindow *window);
    virtual ~MenuState();

    void updateKeybinds(const float &dt);
    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);

protected:
private:
};

#endif // MENUSTATE_H
