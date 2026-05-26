#include <avr/io.h>
#include "serial.h"

int main(void) {
    serial_init();
    
    // D2, D3, D4, D5 como entradas de puerto d con pull up interno
    DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

    char tecla;
    uint32_t timeout = 0;
    uint8_t estado_anterior = 0xFF;

    // las letras mayusculas indican el inicio de la accion
    // las minusculas indican que son continuacion del mismo estado

    while(1) {
        // gamepad
        uint8_t estado_actual = PIND & 0x3C; // leer D2, D3, D4, D5

        if (estado_actual != estado_anterior) {
            // salto
            if (!(estado_actual & (1 << PD4)) && (estado_anterior & (1 << PD4)))
                serial_put_char('K'); // mayus empezar salto
            else if ((estado_actual & (1 << PD4)) && !(estado_anterior & (1 << PD4)))
                serial_put_char('k'); // minus soltar salto

            // deslizar
            if (!(estado_actual & (1 << PD5)) && (estado_anterior & (1 << PD5)))
                serial_put_char('J'); 
            else if ((estado_actual & (1 << PD5)) && !(estado_anterior & (1 << PD5)))
                serial_put_char('j');

            // izquierda
            if (!(estado_actual & (1 << PD2)) && (estado_anterior & (1 << PD2)))
                serial_put_char('A');
            else if ((estado_actual & (1 << PD2)) && !(estado_anterior & (1 << PD2)))
                serial_put_char('a');

            // derechafasfsadfsadfsadfsdfasdfasfsadfasaaaasssddfff
            if (!(estado_actual & (1 << PD3)) && (estado_anterior & (1 << PD3)))
                serial_put_char('D');
            else if ((estado_actual & (1 << PD3)) && !(estado_anterior & (1 << PD3)))
                serial_put_char('d');

            estado_anterior = estado_actual;
        }
    }
}