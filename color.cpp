#include "443ray.hpp"
#include "color.hpp"

Color Color::operator*(REAL t){
    Color ret;
    ret.setColor((UINT8)(red   * t)%256,
                 (UINT8)(green * t)%256,
                 (UINT8)(blue  * t)%256);
    return ret;
};

Color Color::operator+(Color c){
  Color ret;
  ret.setColor((UINT8)(red   + c.red)%256,
                (UINT8)(green + c.green)%256,
                (UINT8)(blue  + c.blue)%256);
  
  return ret;
};

Color::Color(UINT8 r_, UINT8 g_, UINT8 b_){
    red = r_; green = g_; blue = b_;
};

void Color::setColor(UINT8 r_, UINT8 g_, UINT8 b_){
    red = r_; green = g_; blue = b_;
}
