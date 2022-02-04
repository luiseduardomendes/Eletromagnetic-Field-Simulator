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
        if (m1[i].isPositioned() && m1[i].eletric.charge != 1*pow(10,-4))
            e.addNewForceVector(calcEletricField(m1[i], p));

    return e;
}

Coord calcEletricField(ElementarCharge m, Coord p){
    double d = dist(m.kinect.position, p);
    double e = 8.85418782 * pow(10,-12);
    double k = 1/(4 * M_PI * e);
    double v = k * (m.eletric.charge / pow(d*pow(10,1.5), 2));
    
    Coord vet = setUnityVetor(m.kinect.position,p);
    vet.x *= v;
    vet.y *= v;
    vet.z *= v;

    if (abs(d) < 15){
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

bool pointInsideBox(Coord point_, Hitbox box_){
    if (point_.x >= box_.infLeft.x && point_.x <= box_.supRight.x && point_.y >= box_.infLeft.y && point_.y <= box_.supRight.y)
        return true;
    else
        return false;
}

bool pointInsideCircle(Coord point_, Coord center, double radius){
    if(dist(point_, center) <= radius)
        return true;
    else
        return false;
}

bool isHitboxIn(Hitbox HB1, Hitbox HB2){
    Coord aux1, aux2;

    aux1.x = HB2.infLeft.x;
    aux1.y = HB2.supRight.y;

    aux2.x = HB2.supRight.x;
    aux2.y = HB2.infLeft.y;

    if (pointInsideBox(aux1, HB1) || pointInsideBox(aux2, HB1) ||
            pointInsideBox(HB2.infLeft, HB1) || pointInsideBox(HB2.supRight, HB1))
        return true;
    return false;
}

double angleBetweenXAxis(Coord vect1){
    double ang = acos((vect1.x)/sqrt(pow(vect1.x, 2)+pow(vect1.y, 2))) + M_PI;
    if (vect1.y < 0)
        ang *= -1;
    
    return ang;
}