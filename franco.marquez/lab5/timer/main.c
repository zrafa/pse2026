#include "serial.h"
#include "cronometro.h"
#include <avr/interrupt.h>

void main(){
    sei();
    serial_init();
    cronometro_init();
    
    while(1){
        serial_put_char('\r');
        serial_put_char(get_minutos());
        serial_put_char(':');
        serial_put_char(get_segundos());
        serial_put_char(':');
        serial_put_char(get_centesimas());

    }
}
//Main -> cronometro -> timer