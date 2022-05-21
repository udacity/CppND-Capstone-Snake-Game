#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller
{
public:
    bool HandleInput(Snake &snake) const;

private:
    void ChangeDirection(Snake &snake, const Snake::Direction input,
                         const Snake::Direction opposite) const;
};

#endif