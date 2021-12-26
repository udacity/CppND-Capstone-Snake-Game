#include "runner.h"
#include <cmath>
#include <iostream>

void Runner::Active(bool _active)
{
  Object::Active(_active);
  if (!active)
  {
    colour = RBGA{255, 73, 158, 255}; // #FF499E
  }
  else
  {
    colour = RBGA{255, 173, 211, 255}; // #FFADD3
  }
}

void Runner::Shielded(bool _shielded)
{
  shielded = _shield;
  if (_shielded)
  {
    startShield = std::chrono::steady_clock::now();
  }
}

void Runner::Update()
{
  std::chrono::time_point<std::chrono::steady_clock> currentTime;
  std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startShield);
  if (delta > Runner::shieldDuration)
  {
    Shielded(false);
  }
}