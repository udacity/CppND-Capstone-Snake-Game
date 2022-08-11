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

void Player::run(void) {

    // if (snake_->isAlive_) {
    //     controller_->HandleInput(snake_,food_);
    // }


}
}