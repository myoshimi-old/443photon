#ifndef _INC_VECTOR3
#define _INC_VECTOR3

#include "443ray.hpp"

class Vector3{
public:
    REAL x, y, z;
    // コンストラクタ
    Vector3(){};
    Vector3(REAL x_, REAL y_, REAL z_);
    // メソッド
    void setVector(REAL x_, REAL y_, REAL z_);
    void setVector(Vector3 v);
    REAL getVector(int n);
    // 正規化メソッド
    Vector3 normalize();
    // ベクトルの長さを取得
    REAL norm();
    // +演算子の再定義: ベクトル同士の加算
    Vector3 operator+(Vector3 v);
    // -演算子の再定義: ベクトル同士の減算
    Vector3 operator-(Vector3 v);
    // *演算子の再定義: ベクトルに実数tを乗算
    Vector3 operator*(REAL t);
    // *演算子の再定義: ベクトルに実数tを除算
    Vector3 operator/(REAL t);
    // クラスメソッド
    static Vector3 cross(Vector3 a, Vector3 b); // 外積
    static REAL dot(Vector3 a, Vector3 b); // 内積
    void disp();
};

#endif // _INC_VECTOR3
