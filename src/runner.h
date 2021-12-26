#ifndef RUNNER_H
#define RUNNER_H

#include <vector>
#include "SDL.h"
#include "object.h"
#include "utility.h"
class Runner : public Object
{
public:
  Runner(float x, float y);
  ~Runner();
  
  virtual void Update();
  virtual void SetActive(bool _active);
  
  int  GetCoin() const { return purse; }
  void IncrementCoin() { purse++; }
  
  bool GetShielded() const { return shielded; }
  void SetShielded(bool _shield);
  
  void ShiftX(float delta);
    
private:
  int  purse{0};
  bool shielded{false};
  TimeChecker shieldTimer;
};

#endif