#ifndef OBJECT_H
#define OBJECT_H

#include "renderer.h"

struct RBGA
{
    int r, b, g, a;
  	RBGA(): RBGA(255,255,255,255) {}
  	RBGA(int r, int b, int g, int a):
  		r{r}, b{b}, g{g}, a{a}
  	{}

  	~RBGA() {}
};

class Object
{
public:
    Object(float x, float y);
    ~Object() {};

    const RBGA &GetColour() const { return colour; }
    
    float GetX() const { return x; }
    float GetY() const { return y; }
    void SetX(float _x) { x = _x; }
    void SetY(float _y) { y = _y; }
    
    bool GetActive() const { return active; }
    virtual void SetActive(bool _active) { active = _active; }

    virtual void Update() = 0;
    virtual bool Collide(Object *obj);

protected:
    float x, y;
    RBGA  colour;
    bool  active{true};
};


#endif