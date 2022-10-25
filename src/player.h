#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "controller.h"
#include "SDL.h"
#include "snake.h"
#include "channel.h"
#include "settings.h"

namespace SnakeGame {


class Player: public std::enable_shared_from_this<Player>{
public:
    Player(int grid_width, int grid_height, bool isPlayerVirtual,Channel<Message> & chan);
    // Player() : Player(static_cast<int>(SnakeGame::kGridWidth), static_cast<int>(SnakeGame::kGridHeight), true) {};
    ~Player();
    Player(Player const & other) = delete;
    Player(Player && other) = delete;
    Player & operator=(Player const & other) = delete;
    Player & operator=(Player && other) = delete;

    void run(SDL_Point const & food) ;

    bool CheckSnakeEatsFood(SDL_Point const & food);
    bool IsSnakeRunning() const {return running_;};

    Snake * GetSnake() const {return snake_.get();}

    int GetScore() const {return score_;} ;
    std::shared_ptr<Player> get_shared_this() { return shared_from_this(); }


private:
    std::unique_ptr<ControllerBase> controller_;  // every player owns a controller
    std::unique_ptr<Snake> snake_;  // every player controls its own snake
    bool running_{true};
    int score_{0};
    Channel<Message> & chan_;
    
    void Grow();




};

}

#endif