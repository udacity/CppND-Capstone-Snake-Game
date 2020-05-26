#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "actor.h"

void Controller::HandleInput(bool &running, Actor &actor) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          actor.direction = Actor::Direction::kUp;
          break;

        case SDLK_DOWN:
          actor.direction = Actor::Direction::kDown;
          break;

        case SDLK_LEFT:
          actor.direction = Actor::Direction::kLeft;
          break;

        case SDLK_RIGHT:
          actor.direction = Actor::Direction::kRight;
          break;
      }
    }
  }
}