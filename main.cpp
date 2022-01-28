#include "header.hpp"


int main(){
    EletromagField p[NUM_PARTICLES];
    bool particleRemaining;
    double v, d;
    Coord vet;
    float framerate = 60;
    
    int height=600, widht=1000;
    
    if(!al_init())
        std::cout << "Allegro nao pode ser inicializada" << std::endl;

    ALLEGRO_DISPLAY *display = NULL;
    if (!(display = al_create_display(widht, height)))
        std::cout << "Display nao pode ser criado" << std::endl;
    
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_TIMER* frames = al_create_timer(1/60.0);
    al_start_timer(frames);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_timer_event_source(frames));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    while(1){
        /*p[0].setCharge(-5*pow(10, -4));
        p[0].setSpeed(1,0,0);
        p[0].setPosition(100,300,0);
        p[0].setPositionedStatus(true);

        p[1].setCharge(5.0*pow(10, -4));
        p[1].setSpeed(0,0,0);
        p[1].setPosition(200,350,0);
        p[1].setPositionedStatus(true);
        
        p[2].setCharge(5.0*pow(10, -4));
        p[2].setSpeed(0,0,0);
        p[2].setPosition(200,300,0);
        p[2].setPositionedStatus(true);
        
        p[3].setCharge(-2.0*pow(10, -3));
        p[3].setSpeed(2,0,0);
        p[3].setPosition(10,100,0);
        p[3].setPositionedStatus(true);*/
        for (int i = 0; i < 10; i ++){
            p[i] = EletromagField(true);
        }

        
        do{
            ALLEGRO_EVENT event;
            al_wait_for_event(eventQueue, &event);
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                for(int i = 0; i < NUM_PARTICLES; i ++){
                    p[i].setAceleration(0, 0, 0);
                    for (int j = 0; j < NUM_PARTICLES; j ++){
                        if(j != i && p[j].isPositioned() && p[i].isPositioned()){
                            d = dist(p[j], p[i]);
                            v = (1/(4*M_PI*8.85*pow(10,-12))) * (p[i].charge * p[j].charge / pow(d, 2));
                            vet = setUnityVetor(p[j],p[i]);
                            if(abs(d) >= 10)
                                p[i].increaseAceleration(vet.x * v, vet.y * v, vet.z * v * 0);
                            else 
                                p[i].setSpeed(0,0,0);
                        }
                    }
                    p[i].updateSpeed();
                    p[i].moveParticle();
                    Coord pos = p[i].position;
                    if (pos.x > widht-10 || pos.x < 10 || pos.y > height-10 || pos.y < 10)
                        p[i].setPositionedStatus(false);
                    
                }
                
                
                al_clear_to_color(al_map_rgb(5,10,25));
                drawGrid(widht,height);
                for(int i = 0; i < NUM_PARTICLES; i ++)
                    if (p[i].isPositioned())
                        p[i].drawParticle();
                al_flip_display();
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                /*TODO: implement keyboard functions*/
            }
            /*else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                std::cout << al_get_mouse_cursor_position()
            }*/


            particleRemaining = false;

            for (int i = 0; i < NUM_PARTICLES; i ++)
                if (p[i].isPositioned())
                    particleRemaining = true;
            

        } while(particleRemaining);

    }

    return 0;
}