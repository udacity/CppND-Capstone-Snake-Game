#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <memory>
#include "object.h"

class Runner;

class Obstacle : public Object
{
public:
	Obstacle(float x);
    ~Obstacle();
    
    virtual void Update();
    virtual void HitRunner(Runner &runner) = 0;

protected:
    float speed{0.1f};
};

typedef std::unique_ptr<Obstacle> ObstaclePtr;
typedef std::vector<ObstaclePtr>  ObstacleVector;
typedef ObstacleVector::iterator  ObstacleItr;

class Shield : public Obstacle
{
public:
	Shield(float x);
    ~Shield();
    
    void HitRunner(Runner &runner) override;
};

class Coin : public Obstacle
{
public:
	Coin(float x);
    ~Coin();
    
    void HitRunner(Runner &runner) override;
};

class Rock : public Obstacle
{
public:
	Rock(float x);
    ~Rock();
    
    void HitRunner(Runner &runner) override;
};

#endif