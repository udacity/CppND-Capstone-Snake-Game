#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <unordered_map>
#include "snake.h"

class Controller {
 public:
  // Methods
  void HandleInput(bool &running,
                 const std::vector<std::unique_ptr<Snake>> &snakes,
                 std::vector<Uint32> &last_input_ms) const;

 private:
  // Keymaps
  std::vector<std::unordered_map<SDL_Keycode, Snake::Direction>> keymaps {
    {   // Arrow control - Player 1
      {SDLK_UP,    Snake::Direction::kUp},
      {SDLK_DOWN,  Snake::Direction::kDown},
      {SDLK_LEFT,  Snake::Direction::kLeft},
      {SDLK_RIGHT, Snake::Direction::kRight}
    },
    {   // WASD control (qwerty) - Player 2
      {SDLK_w, Snake::Direction::kUp},
      {SDLK_s, Snake::Direction::kDown},
      {SDLK_a, Snake::Direction::kLeft},
      {SDLK_d, Snake::Direction::kRight}
    }
  };

  // Methods
  void ChangeDirection(const std::unique_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif