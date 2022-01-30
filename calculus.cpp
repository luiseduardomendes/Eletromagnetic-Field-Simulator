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

EletricField setEletricFieldVectorinPoint(std::vector<ElementarCharge> *m, int size, Coord p){
    EletricField e = EletricField(p.x, p.y, p.z);

    std::vector<ElementarCharge> &m1 = *m;

    for (int i = 0; i < size; i ++)
        if (m1[i].isPositioned())
            e.addNewForceVector(calcEletricField(m1[i], p));

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

Coord ortogonalVector(Coord vect){
    Coord ort;
    ort.x = vect.y;
    ort.y = -vect.x;
    ort.z = 0;
    return ort;
}
