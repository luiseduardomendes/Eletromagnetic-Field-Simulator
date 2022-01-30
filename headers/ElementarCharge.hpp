#include "header.hpp"

class ElementarCharge{
public:
    ElementarCharge();
    ElementarCharge(bool random);
    ElementarCharge(double x, double y, double z, double charge);

    EletricStatus eletric;
    KinectStatus kinect;

    void setAceleration();
    void moveParticle();
    
    void setPositioned(bool status);
    bool isPositioned();

private:

    bool positioned;
};