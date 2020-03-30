#ifndef GAME_H
#define GAME_H

#include <random>

#include "SDL.h"

#include "controller.h"
#include "EnemyShipManager.h"
#include "renderer.h"
#include "shooter.h"

class Game {
public:
    // constructor
    Game(std::size_t grid_width, std::size_t grid_height);
    
    // methods
    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;

private:
    // private member variables
    Shooter shooter;
    EnemyShipManager enemyShipManager;
    int score{0};
    int level{1};
    bool levelUp = false;
    bool shooterHit = false;
    bool gameOver = false;
    
    // private methods
    void Update();
};

#endif
