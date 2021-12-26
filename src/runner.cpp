#include "runner.h"
#include <cmath>
#include <iostream>

std::chrono::milliseconds Runner::shieldDuration(2000);

Runner::Runner(float x, float y):
	Object(x, y)
{
	SetActive(true);
}

Runner::~Runner() {}

void Runner::SetActive(bool _active)
{
  Object::SetActive(_active);
  if (active)
  {
    colour = RBGA{255, 173, 211, 255}; // #FFADD3
  }
  else
  {
    colour = RBGA{255, 73, 158, 255}; // #FF499E
  }
}

void Runner::SetShielded(bool _shielded)
{
  shielded = _shielded;
  if (shielded)
  {
    startShield = std::chrono::steady_clock::now();
    colour = RBGA{14, 129, 148, 255}; // #0E9594
  }
  else
  {
    colour = RBGA{255, 173, 211, 255}; // #FFADD3
  }
}

void Runner::Update()
{
  std::chrono::time_point<std::chrono::steady_clock> currentTime;
  std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startShield);
  if (delta > Runner::shieldDuration)
  {
    SetShielded(false);
  }
}

void Runner::ShiftX(float delta)
{
  float target = x + delta;
  if (0 <= target)
  {
    SetX(target);
  }
}