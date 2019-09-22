#ifndef STATE_H
#define STATE_H

#include "../../headers/sfml.h"
#include <stack>
#include <iostream>

class State
{
public:
    State(sf::RenderWindow *window);
    virtual ~State();

    const bool &getQuit() const;

    virtual void checkForQuit();
    virtual void updateKeybinds(const float &dt) = 0;

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

protected:
    int _nrOfCredits;

private:
    sf::RenderWindow *_window;
    bool _quit;
};

#endif // STATE_H
