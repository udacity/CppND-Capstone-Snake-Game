#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "controller.h"
#include "SDL.h"
#include "snake.h"

namespace SnakeGame {

class Player{
public:
    Player(int grid_width, int grid_height, bool isPlayerVirtual);
    Player() : Player(static_cast<int>(SnakeGame::kGridWidth), static_cast<int>(SnakeGame::kGridHeight), true) {};
    ~Player() = default;
    Player(Player const & other) = delete;
    Player(Player && other);
    Player & operator=(Player const & other) = delete;
    Player & operator=(Player && other);

    void run(SDL_Point const & food);

    bool CheckSnakeEatsFood(SDL_Point const & food);
    bool IsSnakeRunning() const {return running_;};

    Snake * GetSnake() const {return snake_.get();}

    int GetScore() const {return score_;} ;

private:
    std::unique_ptr<ControllerBase> controller_;  // every player owns a controller
    std::unique_ptr<Snake> snake_;  // every player controls its own snake
    bool running_{true};

    int score_{0};

    void Grow();



};

}

#endif