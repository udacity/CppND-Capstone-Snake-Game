#include "player.h"
#include <iostream>
namespace SnakeGame {
 
Player::Player(int grid_width, int grid_height, bool isPlayerVirtual,Channel<Message> & chan) : 
                    snake_(std::make_unique<Snake>(grid_width,grid_height)),
                    running_(true),
                    score_(0U),
                    chan_(chan)
{
    if (isPlayerVirtual) {
        controller_ = std::make_unique<VirtualController>();
    } else {
        controller_ = std::make_unique<Controller>();
    }
}

Player::~Player() {   
}

void Player::run(SDL_Point const & food) {
    
    Message msg = chan_.waitForStart();
    std::cout << "msg rcv " << (int)(msg.direction) << std::endl;
    running_ = controller_->HandleInput(snake_.get(),food,msg.direction);
}

bool Player::CheckSnakeEatsFood(SDL_Point const & food) {

    int new_x = static_cast<int>(snake_->headX_);
    int new_y = static_cast<int>(snake_->headY_);

    // Check if there's food_ over here
    if ((food.x == new_x) && (food.y == new_y)) {
        Grow();
        return true;
    }
    return false;
}

void Player::Grow() {
    // Grow snake_ and increase speed.
    ++score_;

    snake_->GrowBody();
    snake_->speed_ += 0.02F;
}
}