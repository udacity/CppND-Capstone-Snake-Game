#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "actor.h"

void Controller::ChangeDirection(Actor &actor, Actor::Direction input) const { 
  actor.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Actor &actor) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(actor, Actor::Direction::kUp);
          break;

        case SDLK_DOWN:
          ChangeDirection(actor, Actor::Direction::kDown);
          break;

        case SDLK_LEFT:
          ChangeDirection(actor, Actor::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(actor, Actor::Direction::kRight);
          break;
      }
    }
  }
}