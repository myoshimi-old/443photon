#include"vector3.hpp"

#include<iostream>
#include<cmath>

using namespace std;

Vector3::Vector3(REAL x_, REAL y_, REAL z_){
    x = x_; y = y_; z = z_;
};

void Vector3::setVector(REAL x_, REAL y_, REAL z_){
    x = x_; y = y_; z = z_;
};

void Vector3::setVector(Vector3 v){
    x = v.x; y = v.y; z = v.z;
};

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

Vector3 Vector3::normalize(){
    REAL d;
    Vector3 ret;
    d = sqrt(x * x + y * y + z * z);
    ret.setVector(x/d, y/d, z/d);
    return ret;
};

REAL Vector3::norm(){
    return sqrt(x * x + y * y + z * z);
};

Vector3 Vector3::operator+(Vector3 v){
    Vector3 ret;
    ret.setVector(x+v.x, y+v.y, z+v.z);
    return ret;
};

Vector3 Vector3::operator-(Vector3 v){
    Vector3 ret;
    ret.setVector(x-v.x, y-v.y, z-v.z);
    return ret;
};

Vector3 Vector3::operator*(REAL t){
    Vector3 ret;
    ret.setVector(x*t, y*t, z*t);
    return ret;
};

Vector3 Vector3::operator/(REAL t){
    Vector3 ret;
    ret.setVector(x/t, y/t, z/t);
    return ret;
};

Vector3 Vector3::cross(Vector3 a, Vector3 b){
    Vector3 ret;
    ret.setVector(a.y * b.z - b.y * a.z,
                  a.z * b.x - b.z * a.x,
                  a.x * b.y - b.x * a.y);
    return ret;
};

REAL Vector3::dot(Vector3 a, Vector3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
};

void Vector3::disp(){
    cout << "[" << x << ", " << y << ", " << z << "]" << endl;
};

