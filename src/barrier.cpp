#include "barrier.h"
#include <cmath>
#include <iostream>

bool BarrierSingleton::isInit = false;
std::vector<SDL_Point> BarrierSingleton::body;

BarrierSingleton& BarrierSingleton::getInstance()
{
    static BarrierSingleton    instance;
    if(!isInit)
        init();
    return instance;
}

void BarrierSingleton::init()
{
    isInit = true;
    for (int i = 0; i < 32; i++)
    {
        SDL_Point p;
        p.x = 0;
        p.y = i;
        body.push_back(p);
        p.x = 31;
        p.y = i;
        body.push_back(p);
        p.x = i;
        p.y = 0;
        body.push_back(p);
        p.x = i;
        p.y = 31;
        body.push_back(p);
    }
}

// Inefficient method to check if cell is occupied by snake.
bool BarrierSingleton::BarrierCell(int x, int y) {
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}