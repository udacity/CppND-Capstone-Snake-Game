#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  // We first capture the head's cell before updating (rendering)
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};
  // Update the snake's head position depending on the mode in use
  if (IsAutonomous())  UpdateHeadAutonomous();
  else                 UpdateHeadManual();
  // We then capture the head's cell after updating (rendering)
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHeadManual() {
  // Update head given key-press directions
  // Note: Grid origin -> upper left corner
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateHeadAutonomous() {
  // No update if no plan. Fallback could be added otherwise
  if (planned_path.empty()) return;

  // Get integer (cell) head position (wrapping if needed)
  head_x = std::fmod(head_x + grid_width,  static_cast<float>(grid_width));
  head_y = std::fmod(head_y + grid_height, static_cast<float>(grid_height));
  int x_now = static_cast<int>(head_x);
  int y_now = static_cast<int>(head_y);

  // Pop all waypoints that coincide exactly with our current cell
  while (!planned_path.empty() &&
         planned_path.front() &&
         planned_path.front()->x == x_now &&
         planned_path.front()->y == y_now) {
    planned_path.pop_front();
  }
  if (planned_path.empty()) return;

  // Lambda to take a discrete wrapped step per tick, based on position delta
  auto wrapStep = [](int start, int end, int edge) {
    int d = end - start;
    if (d >  edge/2) d -= edge;
    if (d < -edge/2) d += edge;
    // clamp to {-1, 0, +1}: we only move one cell per tick intention-wise
    return (d > 0) ? 1 : (d < 0 ? -1 : 0);
  };
  // Get next move based on current and next cell differences
  Node* next = planned_path.front();
  int delta_x = wrapStep(x_now, next->x, grid_width);
  int delta_y = wrapStep(y_now, next->y, grid_height);

  // Direction decision-making
  Snake::Direction desired;
  if (delta_x != 0) {
    desired = (delta_x > 0) ? Direction::kRight : Direction::kLeft;
  } else if (delta_y != 0) {
    desired = (delta_y > 0) ? Direction::kDown : Direction::kUp;
  } else {
    // Fallback, already in target cell
    planned_path.pop_front();
    return;
  }

  // Verify direction is feasible
  if (size > 1 && desired == Opposite(direction)) {
    // Trigger replanning and keep current direction for just this tick
    replan_requested = true;
  } else {
    direction = desired;
  }

  // Move one step according to speed (can be fractional)
  switch (direction) {
    case Direction::kUp:    head_y -= speed; break;
    case Direction::kDown:  head_y += speed; break;
    case Direction::kLeft:  head_x -= speed; break;
    case Direction::kRight: head_x += speed; break;
  }
  head_x = std::fmod(head_x + grid_width,  static_cast<float>(grid_width));
  head_y = std::fmod(head_y + grid_height, static_cast<float>(grid_height));
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}