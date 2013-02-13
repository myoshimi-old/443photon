#ifndef _INC_LIGHT
#define _INC_LIGHT

#include "443ray.hpp"
#include "color.hpp"
#include "vector3.hpp"

/** @file */

class Light{
public:
    Vector3 position;
    Color color;
    Light(){};
    Light(Vector3 sv);
    void setPosition(Vector3 sv);
    Vector3 getPosition();
};

#endif // _INC_LIGHT
