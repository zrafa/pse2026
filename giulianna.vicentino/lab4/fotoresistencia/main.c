#include <stdint.h>
#include <util/delay.h>
#include "adc.h"
#include "serial.h"

int main(void) {
    serial_init();
    adc_init();

    uint16_t luz;

    while (1) {
        // leer el PIN A0
        luz = adc_get(0);

        // se envia el valor de 0-1023:
        char buffer[5];
        itoa(luz, buffer, 10);

        for(int i=0; buffer[i] != '\0'; i++) {
            serial_put_char(buffer[i]);
        }
        // se envia \n para que el script lea mas facil
        serial_put_char('\n');

        _delay_ms(200);
    }
}