#include <stdint.h>
#include "serial.h"
#include "timer1.h"

int main(void) {
    serial_init();
    timer1_init();

    while (1) {
        uint8_t dato_raw = serial_get_char();
        
        muestra_actual = ((uint16_t)dato_raw * 290) / 255;
    }
}