#pragma once
#include "header.hpp"

class EletricStatus{
public:
    EletricStatus();
    EletricStatus(bool random);
    EletricStatus(int x, int y);
    
    void setCharge(double);
    
    double charge;

    EletricField eletricFieldResultant = EletricField();
    
};
