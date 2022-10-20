#include "controller.h"
#include "snake.h"

namespace SnakeGame
{
    bool Controller::HandleInput(Snake *snake, SDL_Point const & food, Direction &direction) 
  {

    // SDL_Event e;
    // while (SDL_PollEvent(&e))
    // {
      switch (direction)
      {
      case Direction::kUp:
        snake->ChangeDirection(Direction::kUp,
                        Direction::kDown);
        break;

      case Direction::kDown:
        snake->ChangeDirection(Direction::kDown,
                        Direction::kUp);
        break;

      case Direction::kLeft:
        snake->ChangeDirection(Direction::kLeft,
                        Direction::kRight);
        break;

      case Direction::kRight:
        snake->ChangeDirection(Direction::kRight,
                        Direction::kLeft);
        break;
      case Direction::kQuit:
        return false;
      }
    // }
    return true;
  }

  bool VirtualController::HandleInput(Snake *snake, SDL_Point const & food, Direction &direction)
  {

    // SDL_Event e;
    // while (SDL_PollEvent(&e))
    // {
    if (Direction::kQuit == direction)
    {
      return false;
    }
    // }
  
    routePlanner_.run(snake,food);

    return true;
  }


}