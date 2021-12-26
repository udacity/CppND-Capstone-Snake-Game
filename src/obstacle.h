#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "object.h"
#include "runner.h"

class Obstacle : public Object
{
public:
    virtual void Update();
    virtual bool HitRunner(Runner &runner) = 0;

protected:
    float speed{0.1f};
};

class Shield : public Obstacle
{
public:
    bool HitRunner(Runner &runner);
};

class Coin : public Obstacle
{
public:
    bool HitRunner(Runner &runner);
};

class Rock : public Obstacle
{
public:
    bool HitRunner(Runner &runner);
};

#endif