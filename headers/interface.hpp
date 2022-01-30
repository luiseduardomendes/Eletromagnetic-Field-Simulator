#pragma once
#include "header.hpp"

class Interface{
public:

    void initInterface(int w, int h);
    void loadBitmaps();

    void drawParticle(ElementarCharge e);
    void drawInterface(Coord mouse, ALLEGRO_DISPLAY *display);
    void drawGrid();



    ALLEGRO_BITMAP *posCharge, *negCharge, *eletromagMeter; 
    ALLEGRO_BITMAP *interface;
    int width, height;
};