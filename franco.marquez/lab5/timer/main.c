#include "serial.h"
#include "cronometro.h"
#include <avr/interrupt.h>

void main()
{
    sei();
    serial_init();
    cronometro_init();

    while (1)
    {
        serial_put_char('\r');
        char minutos = get_minutos();

        serial_put_char((minutos / 10) + '0');
        serial_put_char((minutos % 10) + '0');
        serial_put_char(':');

        char segundos = get_segundos();
        serial_put_char((segundos / 10) + '0');
        serial_put_char((segundos % 10) + '0');
        serial_put_char(':');

        char centesimas = get_centesimas();

        serial_put_char((centesimas / 10) + '0');
        serial_put_char((centesimas % 10) + '0');
    }
}
// Main -> cronometro -> timer