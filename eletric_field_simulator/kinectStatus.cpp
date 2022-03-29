#include "headers/header.hpp"

KinectStatus::KinectStatus(){
    setPosition(0,0,0);
    setSpeed(0,0,0);
    setAceleration(0,0,0);
    timeGap = 1/60.0;
    mass = 1;
}

KinectStatus::KinectStatus(bool random){
    position.x = rand() % 1000;
    position.y = rand() % 600;
    position.z = 0;

    setSpeed(0,0,0);
    setAceleration(0,0,0);

    timeGap = 1/60.0;
    mass = 1;
}

void KinectStatus::setPosition(double x_, double y_, double z_){
    position.x = x_;
    position.y = y_;
    position.z = z_;
}
void KinectStatus::setSpeed(double x_, double y_, double z_){
    speed.x = x_;
    speed.y = y_;
    speed.z = z_;
}
void KinectStatus::increaseSpeed(double x_, double y_, double z_){
    speed.x += x_;
    speed.y += y_;
    speed.z += z_;
}
void KinectStatus::increaseAceleration(double x_, double y_, double z_){
    aceleration.x += x_;
    aceleration.y += y_;
    aceleration.z += z_;
}
void KinectStatus::setAceleration(double x_, double y_, double z_){
    aceleration.x = x_;
    aceleration.y = y_;
    aceleration.z = z_;
}

void KinectStatus::updateSpeed(){
    speed.x += aceleration.x * timeGap;
    speed.y += aceleration.y * timeGap;
    speed.z += aceleration.z * timeGap;
}