#pragma once
#include "header.hpp"

class KinectStatus{
public:
    KinectStatus();
    KinectStatus(bool random);

    void setPosition(double, double, double);
    void setSpeed(double, double, double);
    void setAceleration(double, double, double);

    void increaseSpeed(double, double, double);
    void increaseAceleration(double, double, double);
    void updateSpeed();

    Coord position;
    Coord speed;
    Coord aceleration;
    double mass;
    double radius;

    double timeGap;
};
