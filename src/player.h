#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "controller.h"

#include "snake.h"

namespace SnakeGame {

class Player{
public:
    Player(int grid_width, int grid_height, bool isPlayerVirtual);
    Player() : Player(static_cast<int>(SnakeGame::kGridWidth), static_cast<int>(SnakeGame::kGridHeight), true) {};
    ~Player() = default;
    Player(Player const & other) = delete;
    Player(Player && other) = delete;
    Player & operator=(Player const & other) = delete;
    Player & operator=(Player && other) = delete;

    void run();

private:

std::unique_ptr<ControllerBase> controller_;  // every player owns a controller
std::unique_ptr<Snake> snake_;  // every player controls its own snake

};

}

#endif