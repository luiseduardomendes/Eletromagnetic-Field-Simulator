#pragma once
#include "header.hpp"

class EletricStatus{
public:
    EletricStatus();
    EletricStatus(bool random);
    
    void setCharge(float);
    
    float charge;

    EletricField eletricFieldResultant = EletricField();
    
};
