#include "runner.h"
#include <cmath>
#include <iostream>

Runner::Runner(float x, float y):
	Object(x, y),
	shieldTimer(2000)
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
    shieldTimer.Start();
    colour = RBGA{14, 129, 148, 255}; // #0E9594
  }
  else
  {
    colour = RBGA{255, 173, 211, 255}; // #FFADD3
  }
}

void Runner::Update()
{
  if (shieldTimer.DurationPassed())
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