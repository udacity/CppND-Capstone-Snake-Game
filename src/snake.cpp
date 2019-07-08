#include <iostream>
#include <snake.h>
#include <math.h>

Snake::Snake(int grid_width, int grid_height) : grid_width(grid_width), grid_height(grid_height) {
    head_x = grid_width/2;
    head_y = grid_height/2;
}


void Snake::Update() {
    last_dir = dir;
    SDL_Point prev_cell {static_cast<int>(head_x), static_cast<int>(head_y)}; // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell {static_cast<int>(head_x), static_cast<int>(head_y)}; // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
}


void Snake::UpdateHead() {
    switch (dir) {
    case Direction::kUp:
        head_y -= speed;
        head_x = floorf(head_x);
        break;

    case Direction::kDown:
        head_y += speed;
        head_x = floorf(head_x);
        break;

    case Direction::kLeft:
        head_x -= speed;
        head_y = floorf(head_y);
        break;

    case Direction::kRight:
        head_x += speed;
        head_y = floorf(head_y);
        break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    if (head_x < 0) {
        head_x = grid_width - 1;
    } else if (head_x > grid_width) {
        head_x = 0;
    }

    if (head_y < 0) {
        head_y = grid_height - 1;
    } else if (head_y > grid_height) {
        head_y = 0;
    }
}


void Snake::UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell) {
    // Add previous head location to vector
    body.push_back(prev_cell);

    if (!growing) {
        // Remove the tail from the vector.
        body.erase(body.begin());
    } else {
        growing--;
        size++;
    }

    // Check if the snake has died.
    for (auto item:body) {
        if (current_cell.x == item.x && current_cell.y == item.y) {
            alive = false;
        }
    }

}


void Snake::GrowBody(int quantity) {
    growing += quantity;
}


// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    for (auto item:body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}