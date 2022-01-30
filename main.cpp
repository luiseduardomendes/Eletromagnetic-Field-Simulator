#include "headers/header.hpp"
using namespace std;
int main(){
    vector<ElementarCharge> *molecules = new vector<ElementarCharge>;
    vector<ElementarCharge> &p = *molecules;
    EletricField eletricFieldMousePos;

    for(int i = 0; i < 10; i ++)
        p.push_back(ElementarCharge());

    Interface interface;
    Coord mouse;

    bool particleRemaining, exit = false, reset = false, pause = false;
    bool eletroMeterActived = false;
    bool insertPosCharge = false;
    bool insertNegCharge = false;

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

                        //std::cout << e.vectorField.x << ", " << e.vectorField.y << std::endl;
                        
                        p[i].eletric.eletricFieldResultant.setVectorField(e.vectorField.x, e.vectorField.y, e.vectorField.z);
                        p[i].setAceleration();

                        for(int j = 0; j < p.size(); j ++){
                            if (i != j){
                                d = dist(p[i].kinect.position, p[j].kinect.position);
                                if(abs(d) <= 0.015)
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
                for(int i = 0; i < p.size(); i ++)
                    if (p[i].isPositioned())
                        interface.drawParticle(p[i]);
                if(eletroMeterActived){
                    al_draw_textf(font24, al_map_rgb(255,255,255), eletricFieldMousePos.position.x*1000, eletricFieldMousePos.position.y*1000, 0, "E = (%.3f, %.3f, %.3f) N/C", eletricFieldMousePos.vectorField.x, -eletricFieldMousePos.vectorField.y, eletricFieldMousePos.vectorField.z);
                    al_draw_line(eletricFieldMousePos.position.x*1000, eletricFieldMousePos.position.y*1000, (eletricFieldMousePos.position.x*1000 + eletricFieldMousePos.vectorField.x/1000), (eletricFieldMousePos.position.y*1000 + eletricFieldMousePos.vectorField.y/1000), al_map_rgb(140,156,172),2);

                    vetorCampo.x = eletricFieldMousePos.vectorField.x;
                    vetorCampo.y = eletricFieldMousePos.vectorField.y;
                    vetorCampo.z = eletricFieldMousePos.vectorField.z;
                    
                    vetorPosicao.x = eletricFieldMousePos.position.x;
                    vetorPosicao.y = eletricFieldMousePos.position.y;
                    vetorPosicao.z = eletricFieldMousePos.position.z;

                    vetorUnitario = setUnityVetor(vetorPosicao, vetorCampo);
                    ortVetUnit = ortogonalVector(vetorUnitario);

                    cout << "unitario: " << vetorUnitario.x << ", " << vetorUnitario.y << endl;
                    cout << "ortogonal: "<< ortVetUnit.x << ", " << ortVetUnit.y << endl;

                    al_draw_filled_triangle(
                        vetorCampo.x/1000 + vetorPosicao.x*1000 + (vetorUnitario.x * 9), 
                        vetorCampo.y/1000 + vetorPosicao.y*1000 + (vetorUnitario.y * 9), 
                        vetorCampo.x/1000 + vetorPosicao.x*1000 - (ortVetUnit.x * 3), 
                        vetorCampo.y/1000 + vetorPosicao.y*1000 - (ortVetUnit.y * 3), 
                        vetorCampo.x/1000 + vetorPosicao.x*1000 + (ortVetUnit.x * 3),
                        vetorCampo.y/1000 + vetorPosicao.y*1000 + (ortVetUnit.y * 3), 
                        al_map_rgb(140,156,204));
                }

                al_draw_filled_rectangle(widht/2 - 112, height - 112, widht/2 + 184, height - 16, al_map_rgba_f(0.1,0.1,0.1, 0.1));
                al_draw_rectangle(widht/2 - 112, height - 112, widht/2 + 184, height - 16, al_map_rgba_f(0.4,0.4,0.4, 0.4), 5);
                interface.drawInterface(mouse);
                if(eletroMeterActived){
                    al_draw_scaled_bitmap(interface.eletromagMeter, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);
                }
                else if(insertPosCharge){
                    al_draw_scaled_bitmap(interface.posCharge, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);
                }
                else if(insertNegCharge){
                    al_draw_scaled_bitmap(interface.negCharge, 0, 0, 64, 64, mouse.x-16, mouse.y-16, 32,32, 0);

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
                    eletricFieldMousePos = EletricField(event.mouse.x / 1000.0, event.mouse.y / 1000.0, 0);
                    eletricFieldMousePos = setEletricFieldVectorinPoint(molecules, p.size(), eletricFieldMousePos.position);
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if (mouse.x > (widht/2)-96 && mouse.x < (widht/2)-32 && mouse.y > (height)-96 && mouse.y < (height)-32){
                    if(insertPosCharge)
                        insertPosCharge = false;
                    else    
                        insertPosCharge = true;
                    
                }
                else if (mouse.x > (widht/2) && mouse.x < (widht/2)+64 && mouse.y > (height)-96 && mouse.y < (height)-32){
                    if(insertNegCharge)
                        insertNegCharge = false;
                    else    
                        insertNegCharge = true;
                    
                }
                else if (mouse.x > (widht/2)+96 && mouse.x < (widht/2)+160 && mouse.y > (height)-96 && mouse.y < (height)-32){
                    if(eletroMeterActived)
                        eletroMeterActived = false;
                    else    
                        eletroMeterActived = true;
                    
                }
                else{
                    if (insertNegCharge){
                        p.push_back(ElementarCharge(mouse.x / 1000, mouse.y / 1000, 0, -25*pow(10, -9)));
                        
                        insertNegCharge = false;
                    }
                    else if (insertPosCharge){
                        p.push_back(ElementarCharge(mouse.x / 1000, mouse.y / 1000, 0, 25*pow(10, -9)));
                        
                        insertPosCharge = false;
                    }
                }
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