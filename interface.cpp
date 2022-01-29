#include "headers/header.hpp"

void Interface::drawInterface(){
    al_set_target_bitmap(interface);
    al_draw_bitmap(posCharge, 0, 0, 0);
    
}
void Interface::initInterface(int w, int h){
    interface = al_create_bitmap(w/2, h/8);
    width = w;
    height = h;
}

void Interface::drawParticle(ElementarCharge e){
    ALLEGRO_COLOR color;
    
    if(e.eletric.charge < 0)
        color = al_map_rgb(128,128,255);
    else
        color = al_map_rgb(255,128,128);
    al_draw_filled_circle((e.kinect.position.x * 1000), (e.kinect.position.y * 1000), 10, color);
}

void Interface::drawGrid(){
    for (int i = 0; i <= width+100; i += 100)
        al_draw_line(i, 0, i, height, al_map_rgba_f(0.1,0.1,0.1,0.1), 2);
    for (int i = 0; i <= height+100; i += 100)
        al_draw_line(0, i, width, i, al_map_rgba_f(0.1,0.1,0.1,0.1), 2);

    for (int i = 0; i <= width+25; i += 25)
        al_draw_line(i, 0, i, height, al_map_rgba_f(0.1,0.1,0.1,0.1), 1);
    for (int i = 0; i <= height+25; i += 25)
        al_draw_line(0, i, width, i, al_map_rgba_f(0.1,0.1,0.1,0.1), 1);
    
    for (int i = 0; i <= width+5; i += 5)
        al_draw_line(i, 0, i, height, al_map_rgba_f(0.05,0.05,0.05,0.05), 1);
    for (int i = 0; i <= height+5; i += 5)
        al_draw_line(0, i, width, i, al_map_rgba_f(0.05,0.05,0.05,0.05), 1);
}

