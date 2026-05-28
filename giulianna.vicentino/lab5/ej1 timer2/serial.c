
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */


typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */;
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

uart_t *puerto_serial = (uart_t *) (0xc0);//segun el manual arrancan en esta direccion, ademas cada una ocupa 1 byte

#define RECEIVER_ENABLE     (1 << 4)  // RXEN0   0001 0000
#define TRANSMITTER_ENABLE  (1 << 3)  // TXEN0   0000 1000
#define CHARACTER_SIZE_0    (1 << 1)  // UCSZ00  0000 0010
#define CHARACTER_SIZE_1    (1 << 2)  // UCSZ01  0000 0100
#define READY_TO_READ       (1 << 7)  // RXC0    1000 0000
#define READY_TO_WRITE      (1 << 5)  // UDRE0   0010 0000


#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)




void serial_init() {

/*Set baud rate */
puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
puerto_serial->baud_rate_l = (unsigned char)BAUD_PRESCALE;

 puerto_serial->status_control_b = (RECEIVER_ENABLE)|(TRANSMITTER_ENABLE);//es una mascara, se prenden ambos bits al mismo tiempo
/* Set frame format: 8data, 2stop bit */
puerto_serial->status_control_c = (CHARACTER_SIZE_1 | CHARACTER_SIZE_0);
}



void serial_put_char (char c)
{
    //espero que haya algo para leer
  while (!(puerto_serial->status_control_a & READY_TO_WRITE)){ //con un AND verifica si el bit 5 es 0, significa q no hay nada para leer
      }
   
    puerto_serial->data_es = c; 

}


char serial_get_char(void)
{    
    while (!(puerto_serial->status_control_a & READY_TO_READ)){
    }

    return puerto_serial->data_es; 
}



