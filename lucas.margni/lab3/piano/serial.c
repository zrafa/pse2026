
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej uint8_t */

typedef struct {
    uint8_t status_control_a;   /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;   /* ucsr0b USART Control and Status B */
    uint8_t status_control_c;   /* ucsr0c USART Control and Status C */
    uint8_t _reserved;          /* espacio sin utilizar */
    uint8_t baud_rate_l;        /* ubrr0l baud rate low */
    uint8_t baud_rate_h;        /* ubrr0h baud rate high */

    uint8_t data_es;            /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define EN_RX (1<<4) // habilitar recepcion
#define EN_TX (1<<3) // habilitar transmicion

/* rutina de inicializacion */
void serial_init() {
    /* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE >> 8);
    puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

    /* Activar la recepcion y transmicion */
    puerto_serial->status_control_b = (unsigned char) (EN_RX | EN_TX);

    /* Configurar un frame de 8bits, sin bit de paridad y bit de stop */
    uint8_t ocho_bits = (1 << 2) | (1 << 1);
    puerto_serial->status_control_c = (unsigned char) (ocho_bits);
    /* Sin bit de paridad: 0 en bits UPMn0 y UPMN1 (4 y 5) del registro
    Un bit de stop: 0 en bit USBS (3) del registro */
}

/* enviar un byte a traves del dispositivo inicializado */
void serial_put_char(char c) {
    /* Esperar hasta que el transmisor este listo para el proximo caracter */

    while (!((puerto_serial->status_control_a >> 5) & 1));

    /* bit UDREn de registro UCSRnA en 1, buffer vacio */

    /* Enviar el caracter por el registro de datos */
    puerto_serial->data_es = (unsigned char) (c);
}

/* recibir un byte a traves del dispositivo inicializado */
char serial_get_char(void) {
    /* Esperar que llegue el proximo caracter */
    while (!((puerto_serial->status_control_a >> 7) & 1));

    /* bit RXCn de registro UCSRnA en 1, data sin leer */

    /* Devolver el valor que se encuentra en el registro de datos */
    return puerto_serial->data_es;
}