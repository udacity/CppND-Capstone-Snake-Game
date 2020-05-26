#include "actor.h"
#include <cmath>
#include <iostream>

void Actor::Update() 
{
  UpdatePosition();

  SDL_Point current_cell{
      static_cast<int>(body_x),
      static_cast<int>(body_y)};  // Capture the actor's cell after updating.
}

void Actor::UpdatePosition() 
{
  switch (direction) 
  {
    case Direction::kUp:
      body_y -= speed;
      break;

    case Direction::kDown:
      body_y += speed;
      break;

    case Direction::kLeft:
      body_x -= speed;
      break;

    case Direction::kRight:
      body_x += speed;
      break;
  }

  // Wrap the Actor around to the beginning if going off of the screen.
  body_x = fmod(body_x + grid_width, grid_width);
  body_y = fmod(body_y + grid_height, grid_height);
}

bool Actor::IsAlive(const SDL_Point& current_cell)
{
    retun alive;
}

SDL_Point GetActorPosition(){
  SDL_Point position;
  position.x = body_x;
  position.y = body_y;
  return position;
}


// Inefficient method to check if cell is occupied by actor.
bool Actor::ActorCell(int x, int y) 
{
  return (x == static_cast<int>(body_x) && y == static_cast<int>(body_y)));
}