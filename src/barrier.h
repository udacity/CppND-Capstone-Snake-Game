#ifndef BARRIER_H
#define BARRIER_H

#include <vector>
#include "SDL.h"

class BarrierSingleton {
 private:
  BarrierSingleton() = default;
 public:
  static BarrierSingleton& getInstance();
  BarrierSingleton(BarrierSingleton const&) = delete;
  void operator=(BarrierSingleton const&)  = delete;
  
  static void init();
  bool BarrierCell(int x, int y);

  static std::vector<SDL_Point> body;

 private:
  static bool isInit;
  int grid_width;
  int grid_height;
};

#endif