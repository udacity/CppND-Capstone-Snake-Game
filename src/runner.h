#ifndef RUNNER_H
#define RUNNER_H

#include <vector>
#include "SDL.h"
#include "renderer.h"
#include "object.h"

class Runner : public Object
{
public:
  void IncrementCoin() { purse++; }
  int  Coin() { return purse; }

  void Shielded(bool _shield) { shielded = _shield; }
  bool Shielded() { return shielded; }

  virtual void Active(bool _active);

  void MoveLeft();
  void MoveRight();
  
private:
  int  purse{0};
  bool shielded{false};
};

#endif