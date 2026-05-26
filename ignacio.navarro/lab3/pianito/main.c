#include <avr/io.h>
#include "serial.h"

#define DO 261
#define RE 293
#define MI 329
#define FA 349

void play_tone(uint16_t frequency) {
    if (frequency == 0) {
        TCCR1B = 0; 
        PORTB &= ~(1 << PB1); 
        return;
    }
    TCCR1A = (1 << COM1A0); 
    TCCR1B = (1 << WGM12) | (1 << CS11); 
    OCR1A = (1000000UL / frequency) - 1;
}

int main(void) {
    serial_init();
    
    // piano pin D9
    DDRB |= (1 << PB1); 

    char tecla;
    uint32_t timeout = 0;

    while(1) {
        // logica pianito
            tecla = serial_get_char();
            timeout = 100000; // valor alto para compensar la velocidad de 16MHz

            if (tecla == 'a')      play_tone(DO);
            else if (tecla == 's') play_tone(RE);
            else if (tecla == 'd') play_tone(MI);
            else if (tecla == 'f') play_tone(FA);
        

        if (timeout > 0) timeout--;
        else play_tone(0);
    }   
}