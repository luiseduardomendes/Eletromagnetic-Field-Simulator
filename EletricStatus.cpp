#include "headers/header.hpp"

EletricStatus::EletricStatus(){
    setCharge(0);
    eletricFieldResultant = EletricField();
}
EletricStatus::EletricStatus(bool random){
    setCharge(((rand() % 101) - 50) * pow(10, -9));
    eletricFieldResultant = EletricField();
}

void EletricStatus::setCharge(double charge_){
    charge = charge_;
}


