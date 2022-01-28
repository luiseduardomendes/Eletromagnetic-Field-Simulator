#include "header.hpp"

int main(){
    EletromagField p[NUM_PARTICLES];
    EletromagField mousePos = EletromagField();
    bool particleRemaining, exit = false;
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

    // TODO: create functions to fonts
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
        for (int i = 0; i < 10; i ++){
            p[i] = EletromagField(false);
        }

        exit = false;
        
        do{
            ALLEGRO_EVENT event;
            al_wait_for_event(eventQueue, &event);
            
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                for(int i = 0; i < NUM_PARTICLES; i ++){
                    p[i].setAceleration(0, 0, 0);
                    for (int j = 0; j < NUM_PARTICLES; j ++){
                        if(j != i && p[j].isPositioned() && p[i].isPositioned()){
                            d = dist(p[j].position, p[i].position);
                            v = (1/(4*M_PI*8.85*pow(10,-12))) * (p[i].charge * p[j].charge / pow(d, 2));
                            vet = setUnityVetor(p[j].position,p[i].position);
                            if(abs(d) >= 15)
                                p[i].increaseAceleration(vet.x * v, vet.y * v, vet.z * v * 0);
                            else 
                                p[i].setSpeed(0,0,0);
                        }
                    }
                    p[i].updateSpeed();
                    p[i].moveParticle();
                    Coord pos = p[i].position;
                    if (pos.x > widht-10 || pos.x < 10 || pos.y > height-10 || pos.y < 10)
                        p[i].setPositionedStatus(true);
                    
                }
                
                al_clear_to_color(al_map_rgb(5,10,25));
                drawGrid(widht,height);
                for(int i = 0; i < NUM_PARTICLES; i ++)
                    if (p[i].isPositioned())
                        p[i].drawParticle();
                al_draw_textf(font24, al_map_rgb(255,255,255), mousePos.position.x, mousePos.position.y, 0, "E = (%.3f, %.3f, %.3f) N/C", mousePos.aceleration.x, -mousePos.aceleration.y, mousePos.aceleration.z);
                al_flip_display();
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                /*TODO: implement keyboard functions*/
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    exit = true;
            }
            
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                mousePos = EletromagField();
                mousePos.position.x = event.mouse.x;
                mousePos.position.y = event.mouse.y;
                mousePos.position.z = 0;
                for (int j = 0; j < NUM_PARTICLES; j ++){
                    if(p[j].isPositioned()){
                        d = dist(p[j].position, mousePos.position);
                        v = (1/(4*M_PI*8.85*pow(10,-12))) * (p[j].charge / pow(d, 2));
                        vet = setUnityVetor(p[j].position,mousePos.position);
                        mousePos.increaseAceleration(vet.x * v, vet.y * v, vet.z * v * 0);
                    }
                }

            }
            



            particleRemaining = false;

            for (int i = 0; i < NUM_PARTICLES; i ++)
                if (p[i].isPositioned())
                    particleRemaining = true;
            

        } while(particleRemaining && !exit);

    }

    return 0;
}