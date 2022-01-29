#include "header.hpp"

int main(){
    MoleculeStatus p[NUM_PARTICLES];
    EletricField eletricFieldMousePos;
    bool particleRemaining, exit = false;
    double v, d;
    Coord vet;
    float framerate = 60;

    ALLEGRO_DISPLAY *display = NULL;

    int height = 600, widht = 1000;

    allegroStart(widht, height, display);

    ALLEGRO_FONT *font24 = al_load_font("fonte.ttf", 24, 0);

    ALLEGRO_TIMER* frames = al_create_timer(1/60.0);
    al_start_timer(frames);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_timer_event_source(frames));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    while(1){
        for (int i = 0; i < 10; i ++)
            p[i] = MoleculeStatus(false);
        
        exit = false;
        
        do{
            ALLEGRO_EVENT event;
            al_wait_for_event(eventQueue, &event);
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                for(int i = 0; i < NUM_PARTICLES; i ++){
                    p[i].setAceleration(0, 0, 0);
                    
                    EletricField e;
                    e = setEletricFieldVectorinPoint(p, p[i].position);
                    Coord v = e.vectorField;
                    p[i].setAceleration(v.x, v.y, v.z);

                    for(int j = 0; j < NUM_PARTICLES; j ++){
                        if (i != j){
                            dist(p[i].position, p[j].position);
                            if(abs(d) <= 15)
                                p[i].setSpeed(0,0,0);
                        }
                    }
                        
                    p[i].updateSpeed();
                    p[i].moveParticle();
                    
                    if (p[i].position.x > widht || p[i].position.x < 0 || p[i].position.y > height || p[i].position.y < 0)
                        p[i].setPositionedStatus(true);
                    
                }
                
                al_clear_to_color(al_map_rgb(5,10,25));
                drawGrid(widht,height);
                for(int i = 0; i < NUM_PARTICLES; i ++)
                    if (p[i].isPositioned())
                        p[i].drawParticle();
                
                al_draw_textf(font24, al_map_rgb(255,255,255), eletricFieldMousePos.position.x, eletricFieldMousePos.position.y, 0, "E = (%.3f, %.3f, %.3f) N/C", eletricFieldMousePos.vectorField.x, -eletricFieldMousePos.vectorField.y, eletricFieldMousePos.vectorField.z);
                al_flip_display();
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                /*TODO: implement keyboard functions*/
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    exit = true;
            }
            
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                EletricField eletricFieldMousePos = EletricField(event.mouse.x, event.mouse.y, 0);
                eletricFieldMousePos = setEletricFieldVectorinPoint(p, eletricFieldMousePos.position);
            }

            /* TODO: create an object ElementarCharge and MoleculeStatus
             * each of these will have some parameters as mass, charge, position, etc.
            */

           /*
            * TODO: create an object EletricMeter and DistanceMeter. Each of these will 
            * have members to do their role
            */
            
            particleRemaining = false;

            for (int i = 0; i < NUM_PARTICLES; i ++)
                if (p[i].isPositioned())
                    particleRemaining = true;
            
        } while(particleRemaining && !exit);
    }
    return 0;
}