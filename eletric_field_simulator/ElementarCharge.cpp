#include "headers/header.hpp"

ElementarCharge::ElementarCharge(){
    kinect = KinectStatus();
    eletric = EletricStatus();
    positioned = true;
}

ElementarCharge::ElementarCharge(bool random){
    kinect = KinectStatus(true);
    eletric = EletricStatus(true);
    positioned = true;
}

ElementarCharge::ElementarCharge(double x, double y, double z, double charge){
    kinect = KinectStatus();
    kinect.position.x = x;
    kinect.position.y = y;
    kinect.position.z = z;
    eletric = EletricStatus();
    eletric.charge = charge;
    eletric.eletricFieldResultant.position = kinect.position;
    positioned = true;
}

void ElementarCharge::moveParticle(){
    kinect.position.x += kinect.speed.x;
    kinect.position.y += kinect.speed.y;
    kinect.position.z += kinect.speed.z;
}

void ElementarCharge::setAceleration(){
    kinect.aceleration.x = eletric.eletricFieldResultant.vectorField.x / kinect.mass;
    kinect.aceleration.y = eletric.eletricFieldResultant.vectorField.y / kinect.mass;
    kinect.aceleration.z = eletric.eletricFieldResultant.vectorField.z / kinect.mass;
}

bool ElementarCharge::isPositioned(){
    return positioned;
}

void ElementarCharge::setPositioned(bool status){
    positioned = status;
}

