#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <snake.h>

class Controller {
  public:

    Controller() {}
    void HandleInput(bool &running, Snake &snake);
};


#endif