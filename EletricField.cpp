#include "headers/header.hpp"

EletricField::EletricField(){
    setVectorField(0,0,0);
    setPosition(0,0,0);
}
EletricField::EletricField(int x,int y,int z){
    setVectorField(0,0,0);
    setPosition(x,y,z);
}
void EletricField::setVectorField(double x, double y, double z){
    vectorField.x = x;
    vectorField.y = y;
    vectorField.z = z;
}
void EletricField::setPosition(int x,int y,int z){
    position.x = x;
    position.y = y;
    position.z = z;
}
void EletricField::addNewForceVector(Coord vect){
    vectorField.x += vect.x;
    vectorField.y += vect.y;
    vectorField.z += vect.z;
}