#include "serial.h"
#include "timer.h"
#include <stdint.h>


void main(){
    serial_init();
    init_timer();

    unsigned char dato = 0;
    uint16_t aux = 0;
    while(1){

        dato = serial_get_char();

        //Escalar dato de 0..255 a 0..290
        aux = (uint16_t)(dato * 290) / 255;

        actualizar_tope(aux);
    
    }
}