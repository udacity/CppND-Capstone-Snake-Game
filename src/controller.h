#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "route_planner.h"

#include "SDL.h"
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

        virtual bool HandleInput(Snake *snake, SDL_Point const & food, Direction &direction)  = 0;

    };

    class Controller : public ControllerBase
    {
    public:
        bool HandleInput(Snake *snake, SDL_Point const & food, Direction &direction)  override;

    };

    class VirtualController : public ControllerBase {
    public:
        bool HandleInput(Snake *snake, SDL_Point const & food, Direction &direction)  override;
    private:
        RoutePlanner routePlanner_{};        
    
    };
}
#endif