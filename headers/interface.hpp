#pragma once
#include "header.hpp"

class Interface{
public:

    void initInterface(int w, int h);
    void loadBitmaps();

    void drawParticle(ElementarCharge e);
    void drawInterface();
    void drawGrid();

private:

    ALLEGRO_BITMAP *posCharge, *negCharge, *eletromagMeter; 
    ALLEGRO_BITMAP *interface;
    int width, height;
};