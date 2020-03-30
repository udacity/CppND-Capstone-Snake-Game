#ifndef SHOOTER_H
#define SHOOTER_H

#include <vector>
#include "SDL.h"

#include "Direction.h"
#include "missile.h"

class Shooter {
public:
    // constructor
    Shooter(int grid_width, int grid_height) :
        center_x(grid_width/2),
        center_y(grid_height-4),
        grid_x(grid_width),
        grid_y(grid_height)
    {
        PopulateBody();
    }

    // methods
    void Update();
    void ShootMissile();
    bool ShooterCell(int x, int y);
    bool ProcessEnemyMissiles(const std::vector<Missile*> & enemyMissiles);

    // member variables
    Direction direction = Direction::kLeft;
    float speed{0.3f};
    float missileSpeed{-1.0f}; // negative because moving up
    bool moving{false};
    float xbuffer{4.5f};
    bool alive{true};
    float center_x;
    float center_y;
    std::vector<SDL_Point> body;
    std::vector<Missile*> missiles;
    int life{3};

private:
    // private methods
    void UpdateCenter();
    void UpdateMissiles();
    void PopulateBody();
    void MoveBody();

    // private member variables
    int grid_x;
    int grid_y;
};

#endif
