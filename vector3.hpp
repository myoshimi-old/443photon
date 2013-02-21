#ifndef _INC_VECTOR3
#define _INC_VECTOR3

#include "443ray.hpp"

using namespace std;
/** @file vector3.hpp
    @class Vector3
    @brief 3次元ベクトル表現クラスヘッダ
 */
class Vector3{
public:
    REAL x, y, z;
    /** @brief コンストラクタ */
    Vector3(){};
    Vector3(REAL x_, REAL y_, REAL z_);
    void setVector(REAL x_, REAL y_, REAL z_);
    void setVector(Vector3 v);
    REAL getVector(int n);
    Vector3 normalize();
    REAL norm();
    Vector3 operator+(Vector3 v);
    Vector3 operator-(Vector3 v);
    Vector3 operator*(REAL t);
    Vector3 operator/(REAL t);
    static Vector3 cross(Vector3 a, Vector3 b); // 外積
    static REAL dot(Vector3 a, Vector3 b); // 内積
    void getGraph(char* str);
    void disp();
};

#endif // _INC_VECTOR3
