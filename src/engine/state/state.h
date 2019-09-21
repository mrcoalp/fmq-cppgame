#ifndef STATE_H
#define STATE_H

class State
{
public:
    State();
    virtual ~State();

protected:
private:
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif // STATE_H
