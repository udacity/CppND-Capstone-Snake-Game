#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "actor.h"

class Controller {
 public:
  void HandleInput(bool &running, Actor &actor) const;
};

#endif