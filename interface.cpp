#include "headers/header.hpp"

void Interface::drawInterface(Coord mouse, ALLEGRO_DISPLAY *display){
    int sizePos = 0, sizeNeg = 0, sizeMet = 0;
    if (mouse.x > (width/2)-96 && mouse.x < (width/2)-32 && mouse.y > (height)-96 && mouse.y < (height)-32)
        sizePos = 32;
    
    else if (mouse.x > (width/2) && mouse.x < (width/2)+64 && mouse.y > (height)-96 && mouse.y < (height)-32)
        sizeNeg = 32;
    
    else if (mouse.x > (width/2)+96 && mouse.x < (width/2)+160 && mouse.y > (height)-96 && mouse.y < (height)-32)
        sizeMet = 32;
        
    al_set_target_bitmap(interface);
    al_clear_to_color(al_map_rgba_f(0,0,0,0));
    
    al_draw_tinted_scaled_bitmap(posCharge, al_map_rgb_f(0.75,0.75,0.75),0, 0, 64, 64, 16 - (sizePos/2), 16 - (sizePos/2), 64+sizePos, 64+sizePos, 1);


    al_draw_tinted_scaled_bitmap(negCharge,al_map_rgb_f(0.75,0.75,0.75), 0, 0, 64, 64, 16 + 96 - (sizeNeg/2), 16 - (sizeNeg/2), 64+sizeNeg, 64+sizeNeg, ALLEGRO_ALIGN_CENTER);

    
    al_draw_tinted_scaled_bitmap(eletromagMeter,al_map_rgb_f(0.75,0.75,0.75), 0, 0, 64, 64, 16 + 192 - (sizeMet/2), 16 - (sizeMet/2), 64+sizeMet, 64+sizeMet, ALLEGRO_ALIGN_CENTER);

    al_set_target_bitmap(al_get_backbuffer(display));   

    al_draw_bitmap(interface, width/2 - 112,height - 112,0); 
    
}
void Interface::initInterface(int w, int h){
    interface = al_create_bitmap(96*3, 96);
    width = w;
    height = h;
    posCharge = al_load_bitmap("assets/proton.png");
    negCharge = al_load_bitmap("assets/eletron.png");
    eletromagMeter = al_load_bitmap("assets/target.png");
}

void Interface::drawParticle(ElementarCharge e){
    ALLEGRO_COLOR color;
    
    if(e.eletric.charge < 0)
        al_draw_scaled_bitmap(negCharge,0,0,64,64,(e.kinect.position.x)-10, (e.kinect.position.y)-10, 20, 20, 0);
    else
        al_draw_scaled_bitmap(posCharge,0,0,64,64,(e.kinect.position.x)-10, (e.kinect.position.y)-10, 20, 20, 0);
    
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

using namespace std;
void Interface::drawButtons(vector<Button> btns, Coord mouse){
    int growth;
    
    for(int i = 0; i < btns.size(); i ++){
        if(pointInsideBox(mouse, btns[i].hitbox))
            growth = 16;
        else
            growth = 0; 
        al_draw_scaled_bitmap(btns[i].bitmap, 0, 0, 64, 64, btns[i].hitbox.infLeft.x - (growth/2), btns[i].hitbox.infLeft.y- (growth/2), 64 + growth, 64 + growth, 0);
    }
}