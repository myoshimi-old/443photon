#ifndef _INC_SPHERE
#define _INC_SPHERE

#include "443ray.hpp"
#include "vector3.hpp"
#include "color.hpp"

/** @file */

class Sphere{
public:
    Vector3 position;
    Color color;
    REAL radix;
    Sphere(){};
    Sphere(Vector3 v, Color c, REAL set_radix);
    REAL intersect(Vector3 viewPoint, Vector3 viewVector);
};

#endif

