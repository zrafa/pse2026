#include "timer0.h"
#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned int ticks = 0;
unsigned int simulated_ticks = 0;

void contar_ticks()
{
    ticks++;
    
    if (ticks == 10) {
        ticks = 0;
        simulated_ticks++;
    }
}

void main()
{
    char cronometro[8] = {'0', '0', ':', '0', '0', ':', '0', '0'};

    timer0_init(MODE_CTC, PRESCALER_64, 250);
    timer0_enable_interrupts(COUNTER_A, contar_ticks);

    serial_init(0);

    sei();

    while (1) {
        /* centisegundos */
        int cs = simulated_ticks % 100;
        cronometro[7] = '0' + (cs % 10);
        cronometro[6] = '0' + (cs / 10);

        /* segundos */
        int seg = (simulated_ticks / 100) % 60;
        cronometro[4] = '0' + (seg % 10);
        cronometro[3] = '0' + (seg / 10);

        /* minutos */
        int min = simulated_ticks / 6000;
        cronometro[1] = '0' + (min % 10);
        cronometro[0] = '0' + ((min / 10) % 10);

        for (char i = 0; i < 8; i++)
            serial_put_char(cronometro[i]);

        serial_put_char('\n');
    }
}