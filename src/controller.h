#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "runner.h"

class Game;

class Controller
{
public:
  void HandleInput(bool &running, Runner &runner) const;
};

#endif