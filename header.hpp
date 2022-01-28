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

#include "campo_eletromagnetico.hpp"
#include "interface.hpp"

double dist(EletromagField e1, EletromagField e2);
Coord setUnityVetor(EletromagField e1, EletromagField e2);
void drawGrid(int w, int h);