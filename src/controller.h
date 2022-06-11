#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
namespace SnakeGame
{
    class Controller
    {
    public:
        bool HandleInput(Snake &snake) const;

    };
}
#endif