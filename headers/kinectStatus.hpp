#pragma once
#include "header.hpp"

class KinectStatus{
public:
    KinectStatus();
    KinectStatus(bool random);

    void setPosition(float, float, float);
    void setSpeed(float, float, float);
    void setAceleration(float, float, float);

    void increaseSpeed(float, float, float);
    void increaseAceleration(float, float, float);
    void updateSpeed();

    Coord position;
    Coord speed;
    Coord aceleration;
    double mass;
    double radius;

    double timeGap;
};
