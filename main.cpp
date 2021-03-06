#include "headers/header.hpp"
using namespace std;
int main(){
    vector<ElementarCharge> *molecules = new vector<ElementarCharge>;
    vector<ElementarCharge> &p = *molecules;
    EletricField eletricFieldMousePos;

    vector<EletricStatus> *arrows = new vector<EletricStatus>;
    vector<EletricStatus> &a = *arrows;

    enum {btn_insertPosCharge, btn_insertNegCharge, btn_activeEletricMeter};
    vector<Button> *buttons = new vector<Button>;
    vector<Button> &b = *buttons;

    int chargeSelected = -1;    

    for(int i = 0; i < 10; i ++)
        p.push_back(ElementarCharge());

    Interface interface;
    Coord mouse;

    bool particleRemaining, exit = false, reset = false, pause = true;
    bool eletroMeterActived = false;
    bool insertPosCharge = false;
    bool insertNegCharge = false;
    bool insertProfCharge = false;
    int changingPos = -1;

    double v, d;
    Coord vet;
    Coord vetorCampo;
    Coord vetorPosicao;
    Coord ortVetUnit;
    Coord vetorUnitario;
    
    double framerate = 60;

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
    interface.font24 = al_load_font("fonts/fonte.ttf", 24, 0);

    ALLEGRO_TIMER* frames = al_create_timer(1/60.0);
    al_start_timer(frames);

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    interface.initInterface(widht, height);

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_timer_event_source(frames));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));

    interface.triangle = al_create_bitmap(9,7);
    interface.arrow = al_create_bitmap(10,25);
    al_set_target_bitmap(interface.triangle);
    al_draw_filled_triangle(0, 3.5, 9, 0, 9, 7, al_map_rgb(140,156,172));

    al_set_target_bitmap(interface.arrow);
    al_draw_filled_rounded_rectangle(3,10,7,25,1,1,al_map_rgba_f(0.25,0.30, 0.35, 0.2));
    al_draw_filled_triangle(0,11,5,0,10,11,al_map_rgba_f(0.25,0.30, 0.35, 0.2));
    al_set_target_bitmap(al_get_backbuffer(display));

    for (int i = 50; i <= widht - 50; i += 50){
        for (int j = 50; j <= height - 50; j += 50){
            a.push_back(EletricStatus(i, j));
        }
    }

    Button btn_buffer;
    btn_buffer.bitmap = al_load_bitmap("assets/proton.png");
    btn_buffer.hitbox.infLeft.x = widht/2 - 148 + 16;
    btn_buffer.hitbox.infLeft.y = height - 96;
    btn_buffer.hitbox.supRight.x = widht/2 - 148 + 80;
    btn_buffer.hitbox.supRight.y = height - 32;

    b.push_back(btn_buffer);

    btn_buffer.bitmap = al_load_bitmap("assets/eletron.png");
    btn_buffer.hitbox.infLeft.x = widht/2 - 32;
    btn_buffer.hitbox.infLeft.y = height - 96;
    btn_buffer.hitbox.supRight.x = widht/2 + 32;
    btn_buffer.hitbox.supRight.y = height - 32;

    b.push_back(btn_buffer);

    btn_buffer.bitmap = al_load_bitmap("assets/target.png");
    btn_buffer.hitbox.infLeft.x = widht/2 + 148 - 80;
    btn_buffer.hitbox.infLeft.y = height - 96;
    btn_buffer.hitbox.supRight.x = widht/2 + 148 - 16;
    btn_buffer.hitbox.supRight.y = height - 32;

    b.push_back(btn_buffer);

    btn_buffer.bitmap = al_load_bitmap("assets/charge.png");
    btn_buffer.hitbox.infLeft.x = widht/2 - 224;
    btn_buffer.hitbox.infLeft.y = height - 96;
    btn_buffer.hitbox.supRight.x = widht/2 + 64 - 224;
    btn_buffer.hitbox.supRight.y = height - 32;

    b.push_back(btn_buffer);

    while(!exit){
        p.clear();

        reset = false;
        
        while(!reset){
            ALLEGRO_EVENT event;
            al_wait_for_event(eventQueue, &event);
            
            if(event.type == ALLEGRO_EVENT_TIMER){
                if (!pause){
                    for(int i = 0; i < p.size(); i ++){
                        p[i].kinect.setAceleration(0, 0, 0);
                        
                        EletricField e(p[i].kinect.position.x, p[i].kinect.position.y, 0);
                        e = setEletricFieldVectorinPoint(molecules, p.size(), p[i].kinect.position);
                        e.vectorField.x *= p[i].eletric.charge;
                        e.vectorField.y *= p[i].eletric.charge;  
                        
                        p[i].eletric.eletricFieldResultant.setVectorField(e.vectorField.x, e.vectorField.y, e.vectorField.z);
                        p[i].setAceleration();

                        for(int j = 0; j < p.size(); j ++){
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
                
                // TODO: remake functions to drawing and optimize;

                al_clear_to_color(al_map_rgb(5,10,25));
                interface.drawGrid();
                interface.drawFieldLines(&a, &p);
                interface.drawCharges(mouse, &p);
                        
                if(eletroMeterActived)                    
                    interface.drawElectroMeter(eletricFieldMousePos);

                interface.drawbgInterface();
                interface.drawButtons(b, mouse);

                if(eletroMeterActived){
                    al_draw_scaled_bitmap(interface.eletromagMeter, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);
                }
                else if(insertPosCharge){
                    al_draw_scaled_bitmap(interface.posCharge, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);
                }
                else if(insertNegCharge){
                    al_draw_scaled_bitmap(interface.negCharge, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);

                }
                if (chargeSelected != -1){
                    al_draw_textf(font24, al_map_rgb(255,255,255), widht - 250, height/2, 0, "carga: %.2eC", p[chargeSelected].eletric.charge);
                    al_draw_textf(font24, al_map_rgb(255,255,255), widht - 250, height/2+30, 0, "Posi????o: (%.2lf, %.2lf)m", p[chargeSelected].kinect.position.x * PSM, p[chargeSelected].kinect.position.y * PSM);
                    al_draw_textf(font24, al_map_rgb(255,255,255), widht - 250, height/2+60, 0, "Massa: %.2ekg", p[chargeSelected].kinect.mass * MASS_CTE);
                }
                
                

                al_flip_display();
            }

            else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
                /*TODO: implement keyboard functions*/
                switch (event.keyboard.keycode){
                case ALLEGRO_KEY_X:
                    reset = true;
                    break;
                case ALLEGRO_KEY_ENTER:
                    for (int i = 0; i < 10; i ++)
                        p.push_back(ElementarCharge(true));
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
            else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                mouse.x = event.mouse.x;
                mouse.y = event.mouse.y;
                if(eletroMeterActived){
                    eletricFieldMousePos = EletricField(event.mouse.x, event.mouse.y, 0);
                    eletricFieldMousePos = setEletricFieldVectorinPoint(molecules, p.size(), eletricFieldMousePos.position);
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                mouse.x = event.mouse.x;
                mouse.y = event.mouse.y;
                if (pointInsideBox(mouse, b[btn_insertPosCharge].hitbox)){
                    if(insertPosCharge)
                        insertPosCharge = false;
                    else   
                        insertPosCharge = true;
                    
                }
                else if (pointInsideBox(mouse, b[btn_insertNegCharge].hitbox)){
                    if(insertNegCharge)
                        insertNegCharge = false;
                    else    
                        insertNegCharge = true;
                    
                }
                else if (pointInsideBox(mouse, b[btn_activeEletricMeter].hitbox)){
                    if(eletroMeterActived)
                        eletroMeterActived = false;
                    else    
                        eletroMeterActived = true;
                    
                }
                
                else if (pointInsideBox(mouse, b[3].hitbox)){
                    if(insertProfCharge)
                        insertProfCharge = false;
                    else    
                        insertProfCharge = true;
                    
                }
                
                
                else{
                    bool found;
                    chargeSelected = -1;
                    for (int i = 0; i < p.size(); i ++){
                        if (pointInsideCircle(mouse, p[i].kinect.position, 10))
                            chargeSelected = i;
                    }
                        
                    if (chargeSelected == -1){
                        found = false;
                        changingPos = -1;
                    }
                    else 
                        p[chargeSelected].isChangingPos = true;
                        changingPos = chargeSelected;
                    
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                if (changingPos != -1){
                    p[changingPos].kinect.position.x = mouse.x;
                    p[changingPos].kinect.position.y = mouse.y;
                    p[changingPos].isChangingPos = false;
                    changingPos = -1;
                }
                else{
                    if (insertNegCharge){
                        p.push_back(ElementarCharge(mouse.x, mouse.y, 0, -25*pow(10, -3)));
                        
                        insertNegCharge = false;
                    }
                    else if (insertPosCharge){
                        p.push_back(ElementarCharge(mouse.x, mouse.y, 0, 25*pow(10, -3)));
                        
                        insertPosCharge = false;
                    }
                    else if (insertProfCharge){
                        p.push_back(ElementarCharge(mouse.x, mouse.y, 0, 1*pow(10, -4)));
                        
                        insertPosCharge = false;
                    }
                }
            }
            else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                exit = true;
                reset = true;
                    
            }

            /* TODO: create an object ElementarCharge and EletricStatus
             * each of these will have some parameters as mass, charge, position, etc.
            */

           /*
            * TODO: create an object EletricMeter and DistanceMeter. Each of these will 
            * have members to do their role
            */
            
            particleRemaining = false;

            for (int i = 0; i < p.size(); i ++)
                if (p[i].isPositioned())
                    particleRemaining = true;
            
            if (!particleRemaining)
                reset = true;
        }
    }
    return 0;
}