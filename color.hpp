#ifndef _INC_COLOR
#define _INC_COLOR

#include "443ray.hpp"

/** @file color.hpp
    @class Color
    @brief 色表現クラスヘッダ
 */
class Color{
public:
    UINT8 red;
    UINT8 green;
    UINT8 blue;
    // コンストラクタ
    Color(){};
    Color(UINT8 r_, UINT8 g_, UINT8 b_);
    // *演算子の再定義: RGB値に実数tを乗算
    Color operator*(REAL t);
    // +演算子の再定義: RGB値同士の加算
    Color operator+(Color c);
    void setColor(UINT8 r_, UINT8 g_, UINT8 b_);
};

#endif // _INC_COLOR
