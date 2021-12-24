#include "runner.h"
#include <cmath>
#include <iostream>

void Runner::Active(bool _active)
{
  Object::Active(_active);
  if (!active)
  {
    colour = RBGA{0xFF, 0x00, 0x00, 0xFF};
  }
  else
  {
    colour = RBGA{0x00, 0x7A, 0xCC, 0xFF};
  }
}