#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Snake &snake) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          if (snake.last_dir != Snake::Direction::kDown || snake.size == 1)
            snake.dir = Snake::Direction::kUp;
          break;

        case SDLK_DOWN:
          if (snake.last_dir != Snake::Direction::kUp || snake.size == 1)
            snake.dir = Snake::Direction::kDown;
          break;

        case SDLK_LEFT:
          if (snake.last_dir != Snake::Direction::kRight || snake.size == 1)
            snake.dir = Snake::Direction::kLeft;
          break;

        case SDLK_RIGHT:
          if (snake.last_dir != Snake::Direction::kLeft || snake.size == 1)
            snake.dir = Snake::Direction::kRight;
          break;
      }
    }
  }
}