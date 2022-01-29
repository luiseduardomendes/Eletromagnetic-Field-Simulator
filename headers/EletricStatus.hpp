#pragma once
#include "header.hpp"

class EletricStatus{
public:
    EletricStatus();
    
    void setCharge(float);
    
    float charge;
    
    EletricField eletricFieldResultant = EletricField();
    
};
