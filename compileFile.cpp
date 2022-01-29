#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    system("g++ main.cpp common.cpp calculus.cpp ElementarCharge.cpp EletricStatus.cpp EletricField.cpp interface.cpp kinectStatus.cpp $(pkg-config --libs allegro-5 allegro_font-5  allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 --cflags) -o eletromag");
    system("./eletromag");
    return 0;
}