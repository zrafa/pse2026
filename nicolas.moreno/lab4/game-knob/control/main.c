#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <stdint.h>
#include "adc.h"
#include "serial.h"

volatile unsigned char * port_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b  = (unsigned char *) 0x24;
volatile unsigned char * pin_b  = (unsigned char *) 0x23;

int main()
{
    serial_init();
    adc_init();

    *ddr_b &= ~1;   
    *port_b |= 1;   

    while(1)
    {
        uint8_t raw_adc = adc_get(0); 
        uint8_t presionado = (*pin_b & 1) ? 0 : 1; 

        serial_put_char('K');
        serial_put_char(raw_adc);
        serial_put_char('B');
        serial_put_char(presionado);

        _delay_ms(15);
    }
    return 0;
}