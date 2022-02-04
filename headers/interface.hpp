#pragma once
#include "header.hpp"

class Interface{
public:

    void initInterface(int w, int h);
    void loadBitmaps();

    void drawParticle(ElementarCharge e);
    void drawInterface(Coord mouse, ALLEGRO_DISPLAY *display);
    void drawGrid();
    void drawButtons(std::vector<Button> btns, Coord mouse);



    ALLEGRO_BITMAP *posCharge, *negCharge, *eletromagMeter, *profCharge; 
    ALLEGRO_BITMAP *interface;
    int width, height;
};