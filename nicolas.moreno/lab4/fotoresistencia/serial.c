#include <stdint.h> 

/* Estructura de datos para que se superponga a los registros */
typedef struct
{
    uint8_t status_control_a; /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved;        /* espacio sin utilizar */
    uint8_t baud_rate_l;      /* ubrr0l baud rate low */
    uint8_t baud_rate_h;      /* ubrr0h baud rate high */
    uint8_t data_es;          /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

#define RECEIVER_ENABLE 0x10    /* RXEN0 Habilitar la recepcion */
#define TRANSMITTER_ENABLE 0x08 /* TXEN0 Habilitar la transmicion */
#define CHARACTER_SIZE_0 0x02   /* UCSZ00 Numero de bits del dato de e/s */
#define CHARACTER_SIZE_1 0x04   /* UCSZ01 Numero de bits del dato de e/s */
#define READY_TO_READ 0x80      /* RXC0 Dato listo para leer */
#define READY_TO_WRITE 0x20     /* UDRE0 Buffer vacio listo para escribir */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

/* Inicialización del puerto serial (¡Solo una vez!) */
void serial_init() {
    /* Set baud rate */
    puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);
    puerto_serial->baud_rate_l = (unsigned char)BAUD_PRESCALE;
    
    /* Enable receiver and transmitter */
    puerto_serial->status_control_b = (RECEIVER_ENABLE)|(TRANSMITTER_ENABLE);
    
    /* Set frame format: 8data, 1stop bit */
    puerto_serial->status_control_c = (CHARACTER_SIZE_1 | CHARACTER_SIZE_0);
}

/* Enviar un byte a traves del dispositivo inicializado */
void serial_put_char (char c)
{
    /* Wait for empty transmit buffer */
    while (!(puerto_serial->status_control_a & READY_TO_WRITE));
    
    /* Put data into buffer, sends the data */
    puerto_serial->data_es = c;
}

/* Recibir un byte */
char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    while (!(puerto_serial->status_control_a & READY_TO_READ));
    
    /* Get and return received data from buffer */
    return puerto_serial->data_es;
}