#pragma once
#include "header.hpp"

class EletricField{
public:
    EletricField();
    EletricField(double x,double y,double z);

    void addNewForceVector(Coord vect);
    void setVectorField(double x, double y, double z);
    void setPosition(double x,double y,double z);
    
    Coord vectorField;
    Coord position;
private:    
};
