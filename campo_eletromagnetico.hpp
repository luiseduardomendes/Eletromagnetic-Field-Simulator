#pragma once
#include "header.hpp"

class MoleculeStatus{
public:
    MoleculeStatus();
    MoleculeStatus(bool random);
    MoleculeStatus(int posx, int posy, int posz, float spdx, float spdy, float spdz, bool posStatus, float charg);
    
    void setPosition(float, float, float);
    void setSpeed(float, float, float);
    void setAceleration(float, float, float);

    void increaseSpeed(float, float, float);
    void increaseAceleration(float, float, float);
    void moveParticle();
    void updateSpeed();
    void setCharge(float);
    void setTimeGap(float);
    
    void setPositionedStatus(bool status);
    bool isPositioned();

    /* TODO: move the function of drawing to an especified class*/
    void drawParticle();

    Coord position;
    float charge;
    Coord speed;
    Coord aceleration;

private:
    float timeGap;
    bool positioned;
};

class EletricField{
public:
    EletricField();
    EletricField(int x,int y,int z);
    void addNewForceVector(Coord vect);
    void setVectorField(double x, double y, double z);
    void setPosition(int x,int y,int z);
    Coord vectorField;
    Coord position;
private:    
};


