#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Game &game) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          game.ShiftRunner(-1);
          break;

        case SDLK_RIGHT:
          game.ShiftRunner(1);
          break;
      }
    }
  }
}