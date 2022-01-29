#include "headers/header.hpp"

int main(){
    ElementarCharge p[NUM_PARTICLES];
    EletricField eletricFieldMousePos;

    Interface interface;

    bool particleRemaining, exit = false, reset = false, pause = false;

    double v, d;
    Coord vet;
    
    float framerate = 60;

    ALLEGRO_DISPLAY *display = NULL;

    int height = 600, widht = 1000;

    if(!al_init())
        std::cout << "Allegro nao pode ser inicializada" << std::endl;

    
    if (!(display = al_create_display(widht, height)))
        std::cout << "Display nao pode ser criado" << std::endl;
    
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // TODO: create functions to fonts

    ALLEGRO_FONT *font24 = al_load_font("fonts/fonte.ttf", 24, 0);

    ALLEGRO_TIMER* frames = al_create_timer(1/60.0);
    al_start_timer(frames);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    interface.initInterface(widht, height);

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_timer_event_source(frames));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    while(!exit){
        for (int i = 0; i < NUM_PARTICLES; i ++)
            p[i] = ElementarCharge(true);
        
        reset = false;
        
        while(!reset){
            ALLEGRO_EVENT event;
            al_wait_for_event(eventQueue, &event);
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                if (!pause){
                    for(int i = 0; i < NUM_PARTICLES; i ++){
                        p[i].kinect.setAceleration(0, 0, 0);
                        
                        EletricField e(p[i].kinect.position.x, p[i].kinect.position.y, 0);
                        e = setEletricFieldVectorinPoint(p, p[i].kinect.position);
                        e.vectorField.x *= p[i].eletric.charge;
                        e.vectorField.y *= p[i].eletric.charge;  

                        //std::cout << e.vectorField.x << ", " << e.vectorField.y << std::endl;
                        
                        p[i].eletric.eletricFieldResultant.setVectorField(e.vectorField.x, e.vectorField.y, e.vectorField.z);
                        p[i].setAceleration();

                        for(int j = 0; j < NUM_PARTICLES; j ++){
                            if (i != j){
                                d = dist(p[i].kinect.position, p[j].kinect.position);
                                if(abs(d) <= 15)
                                    p[i].kinect.setSpeed(0,0,0);
                            }
                        }
                            
                        p[i].kinect.updateSpeed();
                        p[i].moveParticle();
                        
                    }
                }
                
                al_clear_to_color(al_map_rgb(5,10,25));
                interface.drawGrid();
                for(int i = 0; i < NUM_PARTICLES; i ++)
                    if (p[i].isPositioned())
                        interface.drawParticle(p[i]);
                
                al_draw_textf(font24, al_map_rgb(255,255,255), eletricFieldMousePos.position.x, eletricFieldMousePos.position.y, 0, "E = (%.3f, %.3f, %.3f) N/C", eletricFieldMousePos.vectorField.x, -eletricFieldMousePos.vectorField.y, eletricFieldMousePos.vectorField.z);
                al_flip_display();
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                /*TODO: implement keyboard functions*/
                switch (event.keyboard.keycode){
                case ALLEGRO_KEY_ENTER:
                    reset = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    exit = true;
                    reset = true;
                    break;
                case ALLEGRO_KEY_P:
                    if (!pause) 
                        pause = true; 
                    else 
                        pause = false;
                }
            }
            
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                eletricFieldMousePos = EletricField(event.mouse.x, event.mouse.y, 0);
                eletricFieldMousePos = setEletricFieldVectorinPoint(p, eletricFieldMousePos.position);
            }

            /* TODO: create an object ElementarCharge and EletricStatus
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
            
            if (!particleRemaining)
                reset = true;
        }
    }
    return 0;
}