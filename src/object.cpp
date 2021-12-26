#include "object.h"

Object::Object(float x, float y): 
    x{x}, y{y}
{}

bool overlap(float a, float b, float c, float d)
{
    return a <= d && c <= b;
}

bool Object::Collide(Object *obj)
{
    return overlap(x, x + 1, obj->GetX(), obj->GetX() + 1) &&
        overlap(y, y + 1, obj->GetY(), obj->GetY() + 1);
}