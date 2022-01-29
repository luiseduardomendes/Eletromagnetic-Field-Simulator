#pragma once
#include "header.hpp"

class EletricStatus{
public:
    EletricStatus();
    EletricStatus(bool random);
    
    void setCharge(double);
    
    double charge;

    EletricField eletricFieldResultant = EletricField();
    
};
