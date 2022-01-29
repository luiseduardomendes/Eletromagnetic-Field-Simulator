#include "header.hpp"

class ElementarCharge{
public:
    
    EletricStatus eletric = EletricStatus();
    KinectStatus kinect = KinectStatus();

    void setAceleration();
    void moveParticle();
    
    void setPositioned(bool status);
    bool isPositioned();

private:

    bool positioned;
};