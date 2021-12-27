#include "obstacle.h"
#include "runner.h"
#include <iostream>

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
    std::cout << "Runner has received Shield!" << std::endl;
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
    std::cout << "Runner has received Coin!" << std::endl;
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
    if (runner.GetShielded())
    {
        runner.SetShielded(false);
        std::cout << "Runner has hit rock! Shield lost!" << std::endl;
    }
    else
    {
        runner.SetActive(false);
        std::cout << "Runner has hit rock! Game Over!" << std::endl;
    }
}