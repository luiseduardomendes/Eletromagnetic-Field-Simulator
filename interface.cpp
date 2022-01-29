#include "headers/header.hpp"

void Interface::drawInterface(Coord mouse){
    int sizePos = 0, sizeNeg = 0, sizeMet = 0;


    if (mouse.x > (width/2)-128 && mouse.x < (width/2)-64 && mouse.y > (height)-128 && mouse.y < (height)-64){
        sizePos = 32;
        
    }
    else if (mouse.x > (width/2)-32 && mouse.x < (width/2)+32 && mouse.y > (height)-128 && mouse.y < (height)-64){
        sizeNeg = 32;
        
    }
    else if (mouse.x > (width/2)+64 && mouse.x < (width/2)+128 && mouse.y > (height)-128 && mouse.y < (height)-64){
        sizeMet = 32;
        
    }
    al_draw_scaled_bitmap(posCharge, 0, 0, 64, 64, (width/2)-96 - (sizePos/2), height - 96 - (sizePos/2), 64+sizePos, 64+sizePos, ALLEGRO_ALIGN_CENTER);
    al_draw_scaled_bitmap(negCharge, 0, 0, 64, 64, (width/2) - (sizeNeg/2), height - 96 - (sizeNeg/2), 64+sizeNeg, 64+sizeNeg, ALLEGRO_ALIGN_CENTER);
    al_draw_scaled_bitmap(eletromagMeter, 0, 0, 64, 64, (width/2)+96 - (sizeMet/2), height - 96 - (sizeMet/2), 64+sizeMet, 64+sizeMet, ALLEGRO_ALIGN_CENTER);

    
    
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
        al_draw_scaled_bitmap(negCharge,0,0,64,64,(e.kinect.position.x * 1000), (e.kinect.position.y * 1000), 20, 20, 0);
    else
        al_draw_scaled_bitmap(posCharge,0,0,64,64,(e.kinect.position.x * 1000), (e.kinect.position.y * 1000), 20, 20, 0);
    
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

