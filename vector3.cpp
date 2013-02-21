#include"vector3.hpp"

#include<iostream>
#include<cmath>

using namespace std;

/** @file vector3.cpp
    @brief 3次元ベクトル表現クラス実装ファイル
 */

/** @brief 初期化付きコンストラクタ
    @param[in]  x_ x軸上の位置
    @param[in]  y_ y軸上の位置
    @param[in]  z_ z軸上の位置
*/
Vector3::Vector3(REAL x_, REAL y_, REAL z_){
    x = x_; y = y_; z = z_;
};

/** @brief ベクトルに値を設定
    @param[in]  x_ x軸上の位置
    @param[in]  y_ y軸上の位置
    @param[in]  z_ z軸上の位置
*/
void Vector3::setVector(REAL x_, REAL y_, REAL z_){
    x = x_; y = y_; z = z_;
};

void Vector3::getGraph(char* str){
    //strcpy(str, "hoge");
    sprintf(str, "%6.4f|%6.4f|%6.4f", x, y, z);
};

/** @brief ベクトルに値を設定
    @param[in]  v  Vector3オブジェクト
*/
void Vector3::setVector(Vector3 v){
    x = v.x; y = v.y; z = v.z;
};

/** @brief ベクトルの値を取得
    @param[in]  n  0:x, 1:y, 2:z
*/
REAL Vector3::getVector(int n){
    REAL ret;
    switch(n){
    case 0 :
        ret = x;
        break;
    case 1 :
        ret = y;
        break;
    default :
        ret = z;
        break;
    }
    return ret;
};

/** @brief ベクトルを正規化して返す
    @return Vector3クラスのインスタンス
*/
Vector3 Vector3::normalize(){
    REAL d;
    Vector3 ret;
    d = sqrt(x * x + y * y + z * z);
    ret.setVector(x/d, y/d, z/d);
    return ret;
};

/** @brief ベクトルの長さを返す
    @return ベクトルの長さ
*/
REAL Vector3::norm(){
    return sqrt(x * x + y * y + z * z);
};

/** @brief +演算子の再定義
    ベクトル同士の加算
    @param[in] v 加算するベクトル
    @return 加算されたベクトルのインスタンス
*/
Vector3 Vector3::operator+(Vector3 v){
    Vector3 ret;
    ret.setVector(x+v.x, y+v.y, z+v.z);
    return ret;
};

/** @brief -演算子の再定義
    ベクトル同士の減算
    @param[in] v 減算するベクトル
    @return 減算されたベクトルのインスタンス
*/
Vector3 Vector3::operator-(Vector3 v){
    Vector3 ret;
    ret.setVector(x-v.x, y-v.y, z-v.z);
    return ret;
};

/** @brief *演算子の再定義．
    ベクトルの各要素をスカラー倍する．
    @param[in] t 乗算する値
    @return 乗算されたベクトルのインスタンス
*/
Vector3 Vector3::operator*(REAL t){
    Vector3 ret;
    ret.setVector(x*t, y*t, z*t);
    return ret;
};

/** @brief /演算子の再定義．
    @param[in] t 除算する値
    @return 除算されたベクトルのインスタンス
*/
Vector3 Vector3::operator/(REAL t){
    Vector3 ret;
    ret.setVector(x/t, y/t, z/t);
    return ret;
};

/** @brief ベクトル積(外積)を求めるクラスメソッド．
    @param[in] a 被乗数(第1項)
    @param[in] b 乗数(第2項)
    @return 外積のインスタンス
*/
Vector3 Vector3::cross(Vector3 a, Vector3 b){
    Vector3 ret;
    ret.setVector(a.y * b.z - b.y * a.z,
                  a.z * b.x - b.z * a.x,
                  a.x * b.y - b.x * a.y);
    return ret;
};

/** @brief スカラー積(内積)を求めるクラスメソッド．
    @param[in] a 被乗数(第1項)
    @param[in] b 乗数(第2項)
    @return 内積のインスタンス
*/
REAL Vector3::dot(Vector3 a, Vector3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
};

/** @brief ベクトル情報の表示
 */
void Vector3::disp(){
    cout << "[" << x << ", " << y << ", " << z << "]" << endl;
};

