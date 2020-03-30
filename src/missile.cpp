#include "missile.h"

void Missile::UpdateLocation(const int grid_y) {
    y += speed;
    
    if ( ( y < 0 ) || (y > grid_y) ) {
        active = false;
    }
}
