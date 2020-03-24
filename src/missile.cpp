#include "missile.h"

void Missile::UpdateLocation() {
    y += speed;
    active = y > 0;
}
