#pragma once

#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define NUM_PARTICLES 10

typedef struct {
    float x, y, z;
} Coord;


#include "EletricField.hpp"
#include "EletricStatus.hpp"
#include "kinectStatus.hpp"
#include "ElementarCharge.hpp"
#include "interface.hpp"
#include "calculus.hpp"

double dist(Coord p1, Coord p2);
Coord setUnityVetor(Coord p1, Coord p2);
EletricField setEletricFieldVectorinPoint(ElementarCharge *m, Coord p);
void allegroStart(int w, int h, ALLEGRO_DISPLAY *display);
Coord calcEletricField(ElementarCharge m, Coord p);
