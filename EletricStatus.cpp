#include "headers/header.hpp"

EletricStatus::EletricStatus(){
    setCharge(0);
    eletricFieldResultant = EletricField();
}
EletricStatus::EletricStatus(bool random){
    if (rand() % 10 >= 5)
        setCharge(25 * pow(10, -9));
    else
        setCharge(-25 * pow(10, -9));
    eletricFieldResultant = EletricField();
}

void EletricStatus::setCharge(double charge_){
    charge = charge_;
}


