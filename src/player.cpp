#include "player.h"
namespace SnakeGame {

Player::Player(int grid_width, int grid_height, bool isPlayerVirtual) : 
                    snake_(std::make_unique<Snake>(grid_width,grid_height))
{
    if (isPlayerVirtual) {
        controller_ = std::make_unique<VirtualController>();
    } else {
        controller_ = std::make_unique<Controller>();
    }
}

bool Player::run(SDL_Point const & food) {

    return controller_->HandleInput(snake_.get(),food);

}
}