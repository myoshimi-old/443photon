#ifndef _INC_SCREEN
#define _INC_SCREEN

#include <string>
#include "443ray.hpp"
#include "color.hpp"
#include "vector3.hpp"

using namespace std;

class Screen{
public:
    UINT32 width;
    UINT32 height;
    Color* pixel;
    Vector3 topleft, topright, bottomleft, bottomright;
    Screen(UINT32 w_, UINT32 h_);
    Vector3 getViewVector(Vector3 viewPoint, int x, int y);
    void writePng(string file);
};

#endif
