#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "shooter.h"

class Controller {
 public:
  void HandleInput(bool &running, Shooter &shooter) const;

 private:
  void ChangeDirection(Shooter &shooter, Direction input) const;
};

#endif
