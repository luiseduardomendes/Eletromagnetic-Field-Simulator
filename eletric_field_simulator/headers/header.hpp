#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

typedef struct {
    double x, y, z;
} Coord;
typedef struct Hitbox{
    Coord infLeft, supRight;
}Hitbox;

#define PSM 0.001 //PIXEL_SIZE_IN_METERS
#define MASS_CTE 0.001

#include "buttons.hpp"
#include "EletricField.hpp"
#include "EletricStatus.hpp"
#include "kinectStatus.hpp"
#include "ElementarCharge.hpp"
#include "interface.hpp"
#include "calculus.hpp"

double dist(Coord p1, Coord p2);
Coord setUnityVetor(Coord p1, Coord p2);
EletricField setEletricFieldVectorinPoint(std::vector<ElementarCharge> *m, int size, Coord p);
void allegroStart(int w, int h, ALLEGRO_DISPLAY *display);
Coord calcEletricField(ElementarCharge m, Coord p);
Coord ortogonalVector(Coord vect);
bool isHitboxIn(Hitbox HB1, Hitbox HB2);
bool pointInsideBox(Coord point_, Hitbox box_);
bool pointInsideCircle(Coord point_, Coord center, double radius);
double angleBetweenXAxis(Coord vect1);