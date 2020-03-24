#ifndef SHOOTER_H
#define SHOOTER_H

#include <vector>
#include "SDL.h"
#include "missile.h"

class Shooter {
public:
    enum class Direction { kLeft, kRight };

    Shooter(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height),
                                               center_x(grid_width/2), center_y(grid_height-4)
    {
        PopulateBody();
    }

    void Update();
    void ShootMissile();

    bool SnakeCell(int x, int y);

    Direction direction = Direction::kLeft;

    float speed{0.3f};
    float missileSpeed{-1.0f}; // negative because moving up
    bool moving{false};
    //int size{1};
    float xbuffer{4.5f};
    bool alive{true};
    float center_x;
    float center_y;
    std::vector<SDL_Point> body;
    std::vector<Missile> missiles;

private:
    void UpdateCenter();
    void UpdateMissiles();
    void PopulateBody();

    int grid_width;
    int grid_height;
};

#endif
