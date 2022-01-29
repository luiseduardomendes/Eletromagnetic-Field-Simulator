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

#include "calculus.hpp"

#include "EletricStatus.hpp"
#include "EletricField.hpp"
#include "kinectStatus.hpp"
#include "interface.hpp"
#include "ElementarCharge.hpp"

double dist(Coord p1, Coord p2);
Coord setUnityVetor(Coord p1, Coord p2);
void drawGrid(int w, int h);
EletricField setEletricFieldVectorinPoint(EletricStatus *m, Coord p);
void allegroStart(int w, int h, ALLEGRO_DISPLAY *display);
Coord calcEletricField(EletricStatus m, Coord p);
