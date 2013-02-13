#include "light.hpp"

/** @file */

Light::Light(Vector3 sv){
    position.setVector(sv);
};

void Light::setPosition(Vector3 sv){
    position.setVector(sv);
};

Vector3 Light::getPosition(){
    return position;
};
