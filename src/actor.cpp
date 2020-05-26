#include "actor.h"
#include <cmath>
#include <iostream>

void Actor::Update() 
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