#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdint.h>
#include "adc.h"
#include "serial.h"

#define BIT0 1
#define BIT1 2
#define BIT2 4
#define BIT3 8
#define BIT4 16
#define BIT5 32

volatile unsigned char * port_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24;
volatile unsigned char * pin_b = (unsigned char *) 0x23;

/* Declaraciones de funciones */
void led_init(void);
void led_on(void);
void led_off(void);

/* Función auxiliar para imprimir el valor en la terminal */
void print_numero(uint8_t num) {
    char buffer[4];
    int i = 0;
    if (num == 0) { serial_put_char('0'); return; }
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0) {
        serial_put_char(buffer[--i]);
    }
}

int main(void)
{
    serial_init();
    adc_init();
    led_init();
    
    while (1) {
        /* Obtener lectura del ADC desde el pin Analógico A0 (canal 0) */
        uint8_t val = adc_get(0);

        /* Parpadear LED de estado */
        led_on();
        _delay_ms(50);
        led_off();
		
        print_numero(val);
        serial_put_char('\r');
        serial_put_char('\n');
        
        _delay_ms(500);
    }

    return 0;
}

void led_init()
{
    *port_b = 0x0;
    *ddr_b |= (BIT0 | BIT1 | BIT2 | BIT3);
}

void led_on() 
{
    *port_b |= BIT0;
}

void led_off()
{
    *port_b &= ~BIT0;
}