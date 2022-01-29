#include "header.hpp"

MoleculeStatus::MoleculeStatus(){
    setPosition(0,0,0);
    setCharge(0);
    setAceleration(0,0,0);
    setSpeed(0,0,0);
    setTimeGap(1/60.0);
    setPositionedStatus(false);
}

MoleculeStatus::MoleculeStatus(bool random){
    setPosition(rand()%1000,rand()%600,0);
    setCharge(0.001 * ((rand() % 5) - 2.1));
    setAceleration(0,0,0);
    setSpeed(0,0,0);
    setTimeGap(1/60.0);
    setPositionedStatus(true);
}

MoleculeStatus::MoleculeStatus(int posx, int posy, int posz, float spdx, float spdy, float spdz, bool posStatus, float charg){
    setPosition(posx,posy,posz);
    setAceleration(0,0,0);
    setCharge(charg);
    setSpeed(spdx,spdy,spdz);
    setTimeGap(1/60.0);
    setPositionedStatus(posStatus);
}

void MoleculeStatus::setPosition(float x_, float y_, float z_){
    position.x = x_;
    position.y = y_;
    position.z = z_;
}
void MoleculeStatus::setSpeed(float x_, float y_, float z_){
    speed.x = x_;
    speed.y = y_;
    speed.z = z_;
}
void MoleculeStatus::increaseSpeed(float x_, float y_, float z_){
    speed.x += x_;
    speed.y += y_;
    speed.z += z_;
}
void MoleculeStatus::increaseAceleration(float x_, float y_, float z_){
    aceleration.x += x_;
    aceleration.y += y_;
    aceleration.z += z_;
}
void MoleculeStatus::setAceleration(float x_, float y_, float z_){
    aceleration.x = x_;
    aceleration.y = y_;
    aceleration.z = z_;
}
void MoleculeStatus::moveParticle(){
    position.x += speed.x;
    position.y += speed.y;
    position.z += speed.z;
}
void MoleculeStatus::updateSpeed(){
    speed.x += aceleration.x * timeGap;
    speed.y += aceleration.y * timeGap;
    speed.z += aceleration.z * timeGap;
}
void MoleculeStatus::setPositionedStatus(bool status){
    positioned = status;
}
bool MoleculeStatus::isPositioned(){
    return positioned;
}
void MoleculeStatus::setCharge(float charge_){
    charge = charge_;
}
void MoleculeStatus::setTimeGap(float time_){
    timeGap = time_;
}


void MoleculeStatus::drawParticle(){
    ALLEGRO_COLOR color;
    if(charge < 0)
        color = al_map_rgb(128,128,255);
    else
        color = al_map_rgb(255,128,128);
    al_draw_filled_circle(position.x, position.y, 10, color);
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
    position.x += vect.x;
    position.y += vect.y;
    position.z += vect.z;
}