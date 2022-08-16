#include "player.h"
namespace SnakeGame {

Player::Player(int grid_width, int grid_height, bool isPlayerVirtual) : 
                    snake_(std::make_unique<Snake>(grid_width,grid_height)),
                    running_(true),
                    score_(0U)
{
    if (isPlayerVirtual) {
        controller_ = std::make_unique<VirtualController>();
    } else {
        controller_ = std::make_unique<Controller>();
    }
}

Player::Player(Player && other) {

    this->controller_ = std::move(other.controller_);
    this->snake_ = std::move(other.snake_);
    this->running_ = other.running_;
    this->score_ = other.score_;
    other.controller_ = nullptr;
    other.snake_ = nullptr;
    other.running_ = false;
    other.score_ = 0;
}


Player& Player::operator=(Player && other) {
    
    if (this == &other) {
  	    return *this;
    }

    this->controller_ = std::move(other.controller_);
    this->snake_ = std::move(other.snake_);
    this->running_ = other.running_;
    this->score_ = other.score_;
    return *this;
}


void Player::run(SDL_Point const & food) {
    running_ = controller_->HandleInput(snake_.get(),food);
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