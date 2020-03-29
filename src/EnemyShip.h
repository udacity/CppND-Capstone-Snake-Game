#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <vector>

#include "SDL.h"

#include "Direction.h"
#include "missile.h"

class EnemyShip {
public:
    // constructor
    EnemyShip(int x, int y) : ref_x(x), ref_y(y) {
        populateBody();
    };

    // methods
    void moveShip(Direction direction);

    // member variables
    std::vector<SDL_Point> body;
    int ref_x;
    int ref_y;
    
private:
    // private methods
    void populateBody();
};

#endif /* ENEMYSHIP_H */
