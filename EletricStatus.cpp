#include "headers/header.hpp"

EletricStatus::EletricStatus(){
    setCharge(0);
}
EletricStatus::EletricStatus(bool random){
    setCharge(((rand() % 10) - 5) * pow(10, -4));
}

void EletricStatus::setCharge(float charge_){
    charge = charge_;
}


