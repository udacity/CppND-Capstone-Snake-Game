#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Game;

class Controller
{
public:
    void HandleInput(Game &game, Snake &snake) const;

private:
    void ChangeDirection(Snake &snake, Snake::Direction input,
                         Snake::Direction opposite) const;
};

#endif