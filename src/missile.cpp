#include "missile.h"

void Missile::UpdateLocation() {
    y += speed;
    
    //TODO: update to include upper limit
    // missile is only active if it's within the grid
    active = y > 0;
}
