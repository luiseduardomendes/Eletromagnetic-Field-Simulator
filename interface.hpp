#pragma once
#include "header.hpp"

class Interface{
public:
    void drawInterface();
    void initInterface(int w, int h);
    void loadBitmaps();
private:
    ALLEGRO_BITMAP *posCharge, *negCharge, *eletromagMeter; 
    ALLEGRO_BITMAP *interface;
    int width, height;
};