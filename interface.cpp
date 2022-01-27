#include "header.hpp"

void Interface::drawInterface(){
    al_set_target_bitmap(interface);
    al_draw_bitmap(posCharge, 0, 0, 0);
    
}
void Interface::initInterface(int w, int h){
    interface = al_create_bitmap(w/2, h/8);
    width = w/2;
    height = h/2;
}