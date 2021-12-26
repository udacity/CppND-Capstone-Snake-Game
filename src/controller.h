#ifndef CONTROLLER_H
#define CONTROLLER_H

class Runner;

class Controller
{
public:
  void HandleInput(bool &running, Runner &runner) const;
};

#endif