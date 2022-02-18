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
    void drawFieldLines(std::vector<EletricStatus> *a, std::vector<ElementarCharge> *p);
    void drawCharges(Coord mouse, std::vector<ElementarCharge> *p);
    void drawElectroMeter(EletricField mouse);
    void drawbgInterface();
    void equipotentialLines(Coord mouse, std::vector<ElementarCharge> *p, ALLEGRO_DISPLAY* display);

    ALLEGRO_BITMAP *equipotLines;

    ALLEGRO_BITMAP *posCharge, *negCharge, *eletromagMeter, *profCharge; 
    ALLEGRO_BITMAP *interface;
    ALLEGRO_BITMAP *arrow, *triangle;

    ALLEGRO_FONT *font24;
    int width, height;
};