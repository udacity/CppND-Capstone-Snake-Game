#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Shooter &shooter) const;

 private:
  void ChangeDirection(Shooter &shooter, Shooter::Direction input) const;
};

#endif
