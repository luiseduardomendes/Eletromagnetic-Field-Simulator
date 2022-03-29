#include "headers/header.hpp"

EletricStatus::EletricStatus(){
    setCharge(0);
    eletricFieldResultant = EletricField();
}
EletricStatus::EletricStatus(bool random){
    if (rand() % 10 >= 5)
        setCharge(25 * pow(10, -4));
    else
        setCharge(-25 * pow(10, -4));
    eletricFieldResultant = EletricField();
}
EletricStatus::EletricStatus(int x, int y){
    eletricFieldResultant.position.x = x;
    eletricFieldResultant.position.y = y;
}

void EletricStatus::setCharge(double charge_){
    charge = charge_;
}


