#ifndef RUNNER_H
#define RUNNER_H

#include <vector>
#include "SDL.h"
#include "renderer.h"
#include "object.h"

class Runner : public Object
{
public:
  void Update();
  
  int  Coin() { return purse; }
  void IncrementCoin() { purse++; }
  
  bool Shielded() { return shielded; }
  void Shielded(bool _shield);
  
  void Active(bool _active);
  
private:
  int  purse{0};
  bool shielded{false};
  std::chrono::time_point<std::chrono::steady_clock> startShield;

  static std::chrono::milliseconds shieldDuration(2000);
};

#endif