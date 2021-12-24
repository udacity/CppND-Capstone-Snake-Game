#include "object.h"

RBGA::RBGA(int _r, int _b, int _g, int _a):
    r{_r}, b{_b}, g{_g}, a{_a}
{}

Object::Object(float x, float y): 
    x{x}, y{y}
{};

bool overlap(float a, float b, float c, float d)
{
    return a <= d && c <= b;
}

bool Object::Collide(Renderer &renderer, Object &obj)
{
    int width  = renderer.ObjectWidth();
    int height = renderer.ObjectHeight();
    return overlap(x, x + width, obj.x, obj.x + width) &&
        overlap(y, y + height, obj.y, obj.y + height);
}