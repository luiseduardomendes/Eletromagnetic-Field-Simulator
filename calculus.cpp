#include "header.hpp"

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