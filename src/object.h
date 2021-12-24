#ifndef OBJECT_H
#define OBJECT_H

#include "renderer.h"

struct RBGA
{
    int r, b, g, a;
    RBGA(int _r, int _b, int _g, int _a);
}

class Object
{
public:
    Object(float x, float y);
    ~Object() {};

    float GetX() { return x; }
    float GetY() { return y; }
    float SetX(float _x) { x = _x; }
    float SetY(float _y) { y = _y; }
    RBGA &Colour() { return colour; }
    bool  Active() { return active; }
    virtual void Active(bool _active) { active = _active; }

protected:
    float x, y;
    RBGA colour;
    bool  active{true};
    
    virtual void Update() = 0;
    virtual bool Collide(Renderer &renderer, Object &obj);
};


#endif