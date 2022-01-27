#pragma once
#include "header.hpp"

class EletromagField{
public:
    void setPosition(float, float, float);
    void setSpeed(float, float, float);
    void setAceleration(float, float, float);
    void increaseSpeed(float, float, float);
    void increaseAceleration(float, float, float);
    void moveParticle();
    void updateSpeed();
    void setCharge(float);
    void setTimeGap(float);
    float returnCharge();
    Coord returnPosition();
    Coord returnSpeed();
    Coord returnAceleration();
    void setPositionedStatus(bool status);
    bool isPositioned();

    void drawParticle();

private:
    Coord position;
    float charge;
    Coord speed;
    Coord aceleration;
    float timeGap;
    bool positioned;
};


