#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "actor.h"

void Controller::ChangeDirection(Actor &actor, Actor::Direction input,
                                 Actor::Direction opposite) const { 
  actor.direction = input;
  return;
}

void Controller::HandleInput(bool &running, actor &actor) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(actor, actor::Direction::kUp);
          break;

        case SDLK_DOWN:
          ChangeDirection(actor, actor::Direction::kDown);
          break;

        case SDLK_LEFT:
          ChangeDirection(actor, actor::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          ChangeDirection(actor, actor::Direction::kRight);
          break;
      }
    }
  }
}