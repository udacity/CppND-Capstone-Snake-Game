#include "snake.h"
#include <cmath>
#include <iostream>
namespace SnakeGame
{
  void Snake::Update()
  {
    SDL_Point prev_cell{
        static_cast<int>(headX_),
        static_cast<int>(
            headY_)}; // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(headX_),
        static_cast<int>(headY_)}; // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    if ((current_cell.x != prev_cell.x) ||
        (current_cell.y != prev_cell.y))
    {
      UpdateBody(current_cell, prev_cell);
    }
  }

  void Snake::UpdateHead()
  {
    switch (direction_)
    {
    case Direction::kUp:
      headY_ -= speed_;
      break;

    case Direction::kDown:
      headY_ += speed_;
      break;

    case Direction::kLeft:
      headX_ -= speed_;
      break;

    case Direction::kRight:
      headX_ += speed_;
      break;
    }

    // Wrap the Snake around to the beginning if going off of the screen.
    headX_ = fmod(headX_ + gridWidth_, gridWidth_);
    headY_ = fmod(headY_ + gridHeight_, gridHeight_);
  }

  void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
  {
    // Add previous head location to vector
    body_.push_back(prev_head_cell);

    if (!isGrowing_)
    {
      // Remove the tail from the vector.
      body_.erase(body_.begin());
    }
    else
    {
      isGrowing_ = false;
      ++size_;
    }

    // Check if the snake has died.
    for (auto const &item : body_)
    {
      if (current_head_cell.x == item.x && current_head_cell.y == item.y)
      {
        isAlive_ = false;
      }
    }
  }

  void Snake::GrowBody() { isGrowing_ = true; }

  // Inefficient method to check if cell is occupied by snake.
  bool Snake::SnakeCell(int x, int y)
  {
    if (x == static_cast<int>(headX_) && y == static_cast<int>(headY_))
    {
      return true;
    }
    for (auto const &item : body_)
    {
      if ((x == item.x) &&
          (y == item.y))
      {
        return true;
      }
    }
    return false;
  }
}