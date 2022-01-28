#include "header.hpp"

EletromagField::EletromagField(){
    setPosition(0,0,0);
    setCharge(0);
    setAceleration(0,0,0);
    setSpeed(0,0,0);
    setTimeGap(1/60.0);
    setPositionedStatus(false);
}

EletromagField::EletromagField(bool random){
    setPosition(rand()%1000,rand()%600,0);
    setCharge(0.001 * ((rand() % 5) - 2.1));
    setAceleration(0,0,0);
    setSpeed(0,0,0);
    setTimeGap(1/60.0);
    setPositionedStatus(true);
}

EletromagField::EletromagField(int posx, int posy, int posz, float spdx, float spdy, float spdz, bool posStatus, float charg){
    setPosition(posx,posy,posz);
    setAceleration(0,0,0);
    setCharge(charg);
    setSpeed(spdx,spdy,spdz);
    setTimeGap(1/60.0);
    setPositionedStatus(posStatus);
}

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


void EletromagField::drawParticle(){
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