#include "headers/header.hpp"

EletricStatus::EletricStatus(){
    setCharge(0);
}
EletricStatus::EletricStatus(bool random){
    setCharge(((rand() % 21) - 10) * pow(10, -4));
}

void EletricStatus::setCharge(float charge_){
    charge = charge_;
}


