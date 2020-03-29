#include "missile.h"

void Missile::UpdateLocation() {
    y += speed;
    
    if ( ( y < 0 ) || (y > grid_y) ) {
        active = false;
    }
}
