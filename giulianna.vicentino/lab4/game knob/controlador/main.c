#include <stdint.h>
#include <util/delay.h>
#include <stdlib.h> 
#include "adc.h"
#include "serial.h"
#include <avr/io.h>

int main(void) {
    adc_init();
    serial_init();

    DDRD &= ~(1 << 2);
    PORTD |= (1 << 2);

    char buffer[7]; 

    while(1) {
        uint16_t valor_adc = adc_get(0);
        
        itoa(valor_adc, buffer, 10);
        
        for (int i = 0; buffer[i] != '\0'; i++) {
            serial_put_char(buffer[i]);
        }
        serial_put_char('\n');

        if (!(PIND & (1 << 2))) {
            serial_put_char('s');
            serial_put_char('\n'); 
            _delay_ms(150);
        }

        _delay_ms(10); 
    }
    return 0;
}
