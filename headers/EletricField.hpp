#pragma once
#include "header.hpp"

class EletricField{
public:
    EletricField();
    EletricField(int x,int y,int z);

    void addNewForceVector(Coord vect);
    void setVectorField(double x, double y, double z);
    void setPosition(int x,int y,int z);
    
    Coord vectorField;
    Coord position;
private:    
};
