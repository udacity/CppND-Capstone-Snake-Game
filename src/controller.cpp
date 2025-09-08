#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(const std::unique_ptr<Snake> &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) snake->direction = input;
  return;
}

void Controller::HandleInput(bool &running,
                             const std::vector<std::unique_ptr<Snake>> &snakes,
                             std::vector<Uint32> &last_input_ms) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
        for (std::size_t i = 0; i < snakes.size() && i < keymaps.size(); ++i) {
          // Get keymap
          const auto &map = keymaps[i];
          // Search for key
          auto it = map.find(e.key.keysym.sym);
          // Skip if no key found
          if (it == map.end()) continue;
          
          // Otherwise:
          // Update last input to detect player inactivity
          last_input_ms[i] = SDL_GetTicks();
          // Map key 
          switch (it->second) {
            case Snake::Direction::kUp:
              ChangeDirection(snakes[i], Snake::Direction::kUp,
                              Snake::Direction::kDown);
              break;
            case Snake::Direction::kDown:
              ChangeDirection(snakes[i], Snake::Direction::kDown,
                              Snake::Direction::kUp);
              break;
            case Snake::Direction::kLeft:
              ChangeDirection(snakes[i], Snake::Direction::kLeft,
                              Snake::Direction::kRight);
              break;
            case Snake::Direction::kRight:
              ChangeDirection(snakes[i], Snake::Direction::kRight,
                              Snake::Direction::kLeft);
              break;
          }
        }
    }
  }
}