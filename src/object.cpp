#include "object.h"

RBGA::RBGA(int _r, int _b, int _g, int _a):
    r{_r}, b{_b}, g{_g}, a{_a}
{}

Object::Object(float x, float y): 
    x{x}, y{y}
{}

bool overlap(float a, float b, float c, float d)
{
    return a <= d && c <= b;
}

bool Object::Collide(Object &obj)
{
    return overlap(x, x + 1, obj.x, obj.x + 1) &&
        overlap(y, y + 1, obj.y, obj.y + 1);
}