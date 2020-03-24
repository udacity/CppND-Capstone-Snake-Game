#include "shooter.h"
#include <cmath>
#include <iostream>

void Shooter::Update() {
    // We first capture the head's cell before updating.
    SDL_Point prev_cell{ static_cast<int>(center_x), static_cast<int>(center_y)};
    
    UpdateCenter();
    
    // Capture the center's cell after updating.
    SDL_Point current_cell{ static_cast<int>(center_x), static_cast<int>(center_y)};

    // Update all of the body vector items if the shooter's center has moved to a new cell.
    if (current_cell.x != prev_cell.x) {
        PopulateBody();
    }
}

void Shooter::UpdateCenter() {
    switch (direction) {
        case Direction::kLeft:
            if (center_x > 4.5 && moving) {
                center_x -= speed;
            }
            break;

        case Direction::kRight:
            if (center_x < grid_width - 4.5 && moving) {
                center_x += speed;
            }
            break;
    }
}

void Shooter::PopulateBody() {
    body.clear();
    const int x = static_cast<int>(center_x);
    const int y = static_cast<int>(center_y);
    
    std::vector<int> x_rel = {-3, -2, -2, -1, -1,  0,  0,  0,  0,  1,  1,  2,  2,  3};
    std::vector<int> y_rel = { 0, -1,  0,  0,  2, -2, -1,  1,  2,  0,  2, -1,  0,  0};
    
    for (int i = 0; i < x_rel.size(); i++) {
        body.push_back(SDL_Point{x + x_rel[i], y + y_rel[i]});
    }
}

// Inefficient method to check if cell is occupied by snake.
bool Shooter::SnakeCell(int x, int y) {
    if (x == static_cast<int>(center_x) && y == static_cast<int>(center_y)) {
        return true;
    }
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}
