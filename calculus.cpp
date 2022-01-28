#include "header.hpp"

double dist(EletromagField e1, EletromagField e2){
    Coord p1 = e1.position;
    Coord p2 = e2.position;

    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

Coord setUnityVetor(EletromagField e1, EletromagField e2){
    Coord p1 = e1.position;
    Coord p2 = e2.position;

    Coord vet;
    double distance = dist(e1, e2);

    vet.x = (p2.x - p1.x)/distance;
    vet.y = (p2.y - p1.y)/distance;
    vet.z = 0;

    return vet;
}