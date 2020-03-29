#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "shooter.h"

void Controller::ChangeDirection(Shooter &shooter, Direction input) const
{
    if (shooter.direction != input) {
        shooter.direction = input;
    }
    return;
}

void Controller::HandleInput(bool &running, Shooter &shooter) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    ChangeDirection(shooter, Direction::kLeft);
                    shooter.moving = true;
                    break;

                case SDLK_RIGHT:
                    ChangeDirection(shooter, Direction::kRight);
                    shooter.moving = true;
                    break;
                
                case SDLK_DOWN:
                    shooter.moving = false;
                    break;
                        
                case SDLK_SPACE:
                    shooter.ShootMissile();
                    break;
            }
        }
    }
}
