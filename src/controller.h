#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "runner.h"
#include "game.h"

class Controller {
public:
  void HandleInput(bool &running, Game &game) const;
};

#endif