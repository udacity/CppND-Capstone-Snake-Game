#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "object.h"
#include "runner.h"

class Obstacle : public Object
{
protected:
    virtual void Update();
    virtual bool HitRunner(Runner &runner);

    float speed{0.1f};
};

class Shield : public Obstacle
{
protected:
    bool HitRunner(Runner &runner);
};

class Coin : public Obstacle
{
protected:
    bool HitRunner(Runner &runner);
};

class Rock : public Obstacle
{
protected:
    bool HitRunner(Runner &runner);
};

#endif