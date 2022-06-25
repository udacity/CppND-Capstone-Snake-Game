#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
namespace SnakeGame
{
    class ControllerBase {
    public:
        ControllerBase() = default;
        virtual ~ControllerBase() = default;
        ControllerBase(const ControllerBase & other) = default;
        ControllerBase(ControllerBase && other) = default;
        ControllerBase& operator=(const ControllerBase & other) = default;
        ControllerBase& operator=(ControllerBase && other) = default;

        virtual bool HandleInput(Snake &snake) const = 0;

    };

    class Controller : public ControllerBase
    {
    public:
        bool HandleInput(Snake &snake) const override;

    };

    class VirtualController : public ControllerBase {
    public:
        bool HandleInput(Snake &snake) const override;
    };
}
#endif