#include "campo_eletromagnetico.hpp"

void EletromagField::setPosition(float x_, float y_, float z_){
    position.x = x_;
    position.y = y_;
    position.z = z_;
}
void EletromagField::setSpeed(float x_, float y_, float z_){
    speed.x = x_;
    speed.y = y_;
    speed.z = z_;
}
void EletromagField::increaseSpeed(float x_, float y_, float z_){
    speed.x += x_;
    speed.y += y_;
    speed.z += z_;
}
void EletromagField::increaseAceleration(float x_, float y_, float z_){
    aceleration.x += x_;
    aceleration.y += y_;
    aceleration.z += z_;
}
void EletromagField::setAceleration(float x_, float y_, float z_){
    aceleration.x = x_;
    aceleration.y = y_;
    aceleration.z = z_;
}
void EletromagField::moveParticle(){
    position.x += speed.x;
    position.y += speed.y;
    position.z += speed.z;
}
void EletromagField::updateSpeed(){
    speed.x += aceleration.x * timeGap;
    speed.y += aceleration.y * timeGap;
    speed.z += aceleration.z * timeGap;
}
void EletromagField::setPositionedStatus(bool status){
    positioned = status;
}
bool EletromagField::isPositioned(){
    return positioned;
}
void EletromagField::setCharge(float charge_){
    charge = charge_;
}
void EletromagField::setTimeGap(float time_){
    timeGap = time_;
}
float EletromagField::returnCharge(){
    return charge;
}
Coord EletromagField::returnPosition(){
    return position;
}
Coord EletromagField::returnSpeed(){
    return speed;
}
Coord EletromagField::returnAceleration(){
    return aceleration;
}

void EletromagField::drawParticle(){
    ALLEGRO_COLOR color;
    if(charge > 0)
        color = al_map_rgb(128,128,255);
    else
        color = al_map_rgb(255,128,128);
    al_draw_filled_circle(position.x, position.y, 10, color);
}

double dist(EletromagField e1, EletromagField e2){
    Coord p1 = e1.returnPosition();
    Coord p2 = e2.returnPosition();

    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
}

Coord setUnityVetor(EletromagField e1, EletromagField e2){
    Coord p1 = e1.returnPosition();
    Coord p2 = e2.returnPosition();

    Coord vet;
    double distance = dist(e1, e2);

    vet.x = (p2.x - p1.x)/distance;
    vet.y = (p2.y - p1.y)/distance;
    vet.z = 0;

    return vet;
}

void drawGrid(int w, int h){
    for (int i = 0; i <= w+100; i += 100)
        al_draw_line(i, 0, i, h, al_map_rgba_f(0.1,0.1,0.1,0.1), 2);
    for (int i = 0; i <= h+100; i += 100)
        al_draw_line(0, i, w, i, al_map_rgba_f(0.1,0.1,0.1,0.1), 2);

    for (int i = 0; i <= w+25; i += 25)
        al_draw_line(i, 0, i, h, al_map_rgba_f(0.1,0.1,0.1,0.1), 1);
    for (int i = 0; i <= h+25; i += 25)
        al_draw_line(0, i, w, i, al_map_rgba_f(0.1,0.1,0.1,0.1), 1);
    
    for (int i = 0; i <= w+5; i += 5)
        al_draw_line(i, 0, i, h, al_map_rgba_f(0.05,0.05,0.05,0.05), 1);
    for (int i = 0; i <= h+5; i += 5)
        al_draw_line(0, i, w, i, al_map_rgba_f(0.05,0.05,0.05,0.05), 1);

    
}