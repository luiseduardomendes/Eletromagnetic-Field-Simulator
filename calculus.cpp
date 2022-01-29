#include "headers/header.hpp"

double dist(Coord p1, Coord p2){
    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

Coord setUnityVetor(Coord p1, Coord p2){
    Coord vet;
    double distance = dist(p1, p2);

    vet.x = (p2.x - p1.x)/distance;
    vet.y = (p2.y - p1.y)/distance;
    vet.z = 0;

    return vet;
}

EletricField setEletricFieldVectorinPoint(ElementarCharge *m, Coord p){
    EletricField e = EletricField(p.x, p.y, p.z);

    for (int i = 0; i < NUM_PARTICLES; i ++)
        if (m[i].isPositioned())
            e.addNewForceVector(calcEletricField(m[i], p));
            
    
        
    return e;
}

Coord calcEletricField(ElementarCharge m, Coord p){
    double d = dist(m.kinect.position, p);
    double e = 8.85418782 * pow(10,-12);
    double k = 1/(4 * M_PI * e);
    double v = k * (m.eletric.charge / pow(d, 2));
    
    Coord vet = setUnityVetor(m.kinect.position,p);
    vet.x *= v;
    vet.y *= v;
    vet.z *= v;

    if (abs(d) < 0.015){
        vet.x = 0;
        vet.y = 0;
        vet.z = 0;
    }
    return vet;
}

double dist(Coord p1, Coord p2);
Coord setUnityVetor(Coord p1, Coord p2);
EletricField setEletricFieldVectorinPoint(EletricStatus *m, Coord p);
Coord calcEletricField(EletricStatus m, Coord p);