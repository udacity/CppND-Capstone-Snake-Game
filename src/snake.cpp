#include "snake.h"
#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
namespace SnakeGame
{

unsigned char getRandomColour() {
    std::random_device randDev;
    std::mt19937 randEngine{randDev()};
    std::uniform_int_distribution<unsigned char> randomColour{std::numeric_limits<unsigned char>::min(), std::numeric_limits<unsigned char>::max()};

    return randomColour(randEngine);
}

Snake::Snake(int grid_width, int grid_height,bool isPlayerVirtual)
        : gridWidth_(grid_width),
          gridHeight_(grid_height) {

  std::random_device randDev;
  std::mt19937 randEngine{randDev()};
  std::uniform_int_distribution<int> randomWidth{0, static_cast<int>(grid_width - 1)};
  std::uniform_int_distribution<int> randomHeight{0, static_cast<int>(grid_height - 1)};

  headX_ = static_cast<float>(randomWidth(randEngine));
  headY_ = static_cast<float>(randomHeight(randEngine));

  if (isPlayerVirtual) {
    // let's change the colour of the body of the snake for some random colors
    colour_.red_ = getRandomColour();
    colour_.green_ = getRandomColour();
    colour_.blue_ = getRandomColour();
  }

}

void Snake::Update()
{

  std::unique_ptr<SDL_Point> prev_cell = std::make_unique<SDL_Point>();
    prev_cell->x = static_cast<int>(headX_);
    prev_cell->y = static_cast<int>(headY_); // We first capture the head's cell before updating.
  UpdateHead();
  std::unique_ptr<SDL_Point> current_cell = std::make_unique<SDL_Point>();
    current_cell->x = static_cast<int>(headX_);
    current_cell->y = static_cast<int>(headY_); // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if ((current_cell->x != prev_cell->x) ||
      (current_cell->y != prev_cell->y))    {
    UpdateBody(std::move(current_cell), std::move(prev_cell));
  }
}

void Snake::ChangeDirection(const Direction input, const Direction opposite) {

  if ((opposite != direction_) || 
      (1U == size_))
  {
    direction_ = input;
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
  case Direction::kQuit:
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  headX_ = fmod(headX_ + gridWidth_, gridWidth_);
  headY_ = fmod(headY_ + gridHeight_, gridHeight_);
}

void Snake::UpdateBody(std::unique_ptr<SDL_Point> current_head_cell, std::unique_ptr<SDL_Point> prev_head_cell)
{
  // Add previous head location to vector
  body_.push_back(std::move(prev_head_cell));

  if (!isGrowing_)
  {
    // Remove the tail from the vector.
    body_.erase(body_.begin());
  } else {
    isGrowing_ = false;
    ++size_;
  }

  auto checkIsAlive = [&](std::unique_ptr<SDL_Point> &point) {
    if ( (current_head_cell->x == point->x) && 
          (current_head_cell->y == point->y) )
    {
      isAlive_ = false;
    }
  };
  // Check if the snake has died.
  std::for_each(body_.begin(), body_.end(), checkIsAlive);

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
    if ((x == item->x) &&
        (y == item->y))
    {
      return true;
    }
  }
  return false;
}
}