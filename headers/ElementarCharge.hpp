#include "header.hpp"

class ElementarCharge{
public:
    ElementarCharge();
    ElementarCharge(bool random);

    EletricStatus eletric;
    KinectStatus kinect;

    void setAceleration();
    void moveParticle();
    
    void setPositioned(bool status);
    bool isPositioned();

private:

    bool positioned;
};