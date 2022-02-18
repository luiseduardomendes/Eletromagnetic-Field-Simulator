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
    equipotLines = al_create_bitmap(w, h);
    posCharge = al_load_bitmap("assets/proton.png");
    negCharge = al_load_bitmap("assets/eletron.png");
    eletromagMeter = al_load_bitmap("assets/target.png");
    profCharge = al_load_bitmap("assets/charge.png");
}

void Interface::drawParticle(ElementarCharge e){
    ALLEGRO_COLOR color;
    
    if(e.eletric.charge < 0)
        al_draw_scaled_bitmap(negCharge,0,0,64,64,(e.kinect.position.x)-10, (e.kinect.position.y)-10, 20, 20, 0);
    else if (e.eletric.charge != 1*pow(10,-4))
        al_draw_scaled_bitmap(posCharge,0,0,64,64,(e.kinect.position.x)-10, (e.kinect.position.y)-10, 20, 20, 0);
    else
        al_draw_scaled_bitmap(profCharge,0,0,64,64,(e.kinect.position.x)-10, (e.kinect.position.y)-10, 20, 20, 0);

    
}

//todo calculo

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

void Interface::drawFieldLines(vector<EletricStatus> *a, vector<ElementarCharge> *p){
    for(int i = 0; i < a->size(); i ++){
        Coord vect = setEletricFieldVectorinPoint(p, p->size(), (*a)[i].eletricFieldResultant.position).vectorField;
        (*a)[i].eletricFieldResultant.setVectorField(vect.x, vect.y, 0);
        
        al_draw_rotated_bitmap(arrow, 5, 12.5, (*a)[i].eletricFieldResultant.position.x, (*a)[i].eletricFieldResultant.position.y, angleBetweenXAxis((*a)[i].eletricFieldResultant.vectorField) - (M_PI / 2), 0);
    }
}

void Interface::drawCharges(Coord mouse, vector<ElementarCharge> *p){
    for(int i = 0; i < (*p).size(); i ++)
        if ((*p)[i].isPositioned() && !(*p)[i].isChangingPos)
            drawParticle((*p)[i]);
        else if ((*p)[i].isChangingPos){
            if ((*p)[i].eletric.charge > 0)
                al_draw_scaled_bitmap(posCharge, 0, 0, 64, 64, mouse.x-10, mouse.y-10, 20,20, 0);
            else
                al_draw_scaled_bitmap(negCharge, 0, 0, 64, 64, mouse.x-10, mouse.y-10, 20,20, 0);
        }
}

void Interface::drawElectroMeter(EletricField mouse){

    al_draw_textf(font24, al_map_rgb(255,255,255), mouse.position.x, 
    mouse.position.y, 0, "E = (%.3f, %.3f, %.3f) N/C", mouse.vectorField.x, 
    -mouse.vectorField.y, mouse.vectorField.z);

    al_draw_line(mouse.position.x, mouse.position.y, 
    (mouse.position.x + mouse.vectorField.x), 
    (mouse.position.y + mouse.vectorField.y), al_map_rgb(140,156,172),2);

    al_draw_rotated_bitmap(triangle, 4.5, 3.5, 
    mouse.position.x + mouse.vectorField.x, 
    mouse.position.y + mouse.vectorField.y, 
    angleBetweenXAxis(mouse.vectorField), 0);
}

void Interface::drawbgInterface(){
    al_draw_filled_rectangle(width/2 - 240, height - 112, width/2 + 240, height - 16, al_map_rgba_f(0.1,0.1,0.1, 0.1));
    al_draw_rectangle(width/2 - 240, height - 112, width/2 + 240, height - 16, al_map_rgba_f(0.4,0.4,0.4, 0.4), 5);
}

void Interface::equipotentialLines(Coord mouse, vector<ElementarCharge> *p, ALLEGRO_DISPLAY* display){
    al_set_target_bitmap(equipotLines);
    Coord newPos, vet;
    newPos = mouse;
    do {
        al_draw_pixel(newPos.x, newPos.y, al_map_rgb(0,0,0));
        vet = ortogonalVector(setEletricFieldVectorinPoint(p, p->size(), newPos).vectorField);
        cout << newPos.x << " " << newPos.y << " " << mouse.x << " " << mouse.y << " ";
        cout << vet.x << " " << vet.y << endl;
        newPos.x += vet.x;
        newPos.y += vet.y;
    } while(newPos.x != mouse.x && newPos.y != mouse.y);

    al_set_target_bitmap(al_get_backbuffer(display));
        
}
                