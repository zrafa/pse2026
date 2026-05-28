
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> 


#include "serial.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#define RXEN0  4
#define TXEN0  3
#define UCSZ01 2
#define UCSZ00 1
#define UDRE0  5
#define RXC0   7

typedef struct
{
    uint8_t status_control_a;    /* 0xC0: UCSR0A */
    uint8_t status_control_b;    /* 0xC1: UCSR0B */
    uint8_t status_control_c;    /* 0xC2: UCSR0C */
    uint8_t reserved;            /* 0xC3: espacio reservado*/
    uint8_t baud_rate_low;       /* 0xC4: UBRR0L */
    uint8_t baud_rate_high;      /* 0xC5: UBRR0H */
    uint8_t data_es;             /* 0xC6: UDR0 */
} volatile uart_t;


uart_t *puerto_serial = (uart_t *) (0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void serial_init() {
	
    /* configurar el baud rate */
    puerto_serial->baud_rate_high = (uint8_t)(BAUD_PRESCALE >> 8);
    puerto_serial->baud_rate_low  = (uint8_t)(BAUD_PRESCALE);

    /* UCSZ01 y UCSZ00 en 1 para 8 bits. Paridad y Stop están en 0 por defecto. */
    puerto_serial->status_control_c = (1 << UCSZ01) | (1 << UCSZ00);

    /* 3. Activar la recepción (RX) y la transmisión (TX) */
    puerto_serial->status_control_b = (1 << RXEN0) | (1 << TXEN0);
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
   
    /* esperar hasta que el bit UDRE0 sea 1 */
    while (!(puerto_serial->status_control_a & (1 << UDRE0))) {
        // espera activa
    }

    puerto_serial->data_es = c;
}


char serial_get_char(void)
{
   
    /* esperar hasta que el bit RXC0 sea 1 */
    while (!(puerto_serial->status_control_a & (1 << RXC0))) {
        // espera activa
    }

    return puerto_serial->data_es;
}