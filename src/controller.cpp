#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, Runner &runner) const
{
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
          runner.ShiftX(-1);
          break;

        case SDLK_RIGHT:
          runner.ShiftX(1);
          break;
      }
    }
  }
}