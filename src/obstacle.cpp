#include "obstacle.h"
#include "runner.h"

// -------------------- OBSTACLE --------------------

Obstacle::Obstacle(float x) : Object(x, 0) {}

Obstacle::~Obstacle() {}

void Obstacle::Update()
{
  y += speed;
}

void Obstacle::HitRunner(Runner &runner)
{
    SetActive(false);
}

// -------------------- SHIELD --------------------
// TODO: Add colours

// #0E9594
Shield::Shield(float x): Obstacle(x)
{
      colour = RBGA(14, 149, 148, 255);
}

Shield::~Shield() {}

void Shield::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.SetShielded(true);
}

// -------------------- COIN --------------------

// #FCBA04
Coin::Coin(float x): Obstacle(x)
{
      colour = RBGA(252, 186, 4, 244);
}

Coin::~Coin() {}

void Coin::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    runner.IncrementCoin();
}

// -------------------- ROCK --------------------

// #7B2D26
Rock::Rock(float x): Obstacle(x)
{
    colour = RBGA(123, 45, 38, 255);
}

Rock::~Rock() {}

void Rock::HitRunner(Runner &runner)
{
    Obstacle::HitRunner(runner);
    if (!runner.GetShielded())
    {
        runner.SetActive(false);        
    }
}