#include "header.hpp"

void ElementarCharge::moveParticle(){
    kinect.position.x += kinect.speed.x;
    kinect.position.y += kinect.speed.y;
    kinect.position.z += kinect.speed.z;
}

void ElementarCharge::setAceleration(){
    kinect.aceleration = eletric.eletricFieldResultant.vectorField;
}

void ElementarCharge::setPositioned(bool status){
    positioned = true;
}