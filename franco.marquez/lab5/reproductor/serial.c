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


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    //Desde 0xC6 UDR0 hasta 0xC0 UCSR0A
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;   // UCSR0B
    uint8_t status_control_c;   //UCSROC

    uint8_t reservado; // Espacio Reservado
    
    uint8_t UBRR0L; // Parte Low de los 16 bits
    uint8_t UBRR0H; // Parte High de los 16 (usamos 4 de 8)

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

#define USART_BAUDRATE 115200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

#define RXEN0 4
#define TXEN0 3
#define USBS0 3
#define UCSZ00 1
#define UDREn 5
#define RXCn 7
void serial_init() {    

        /*Set baud rate */
        puerto_serial->UBRR0H = (unsigned char)(BAUD_PRESCALE>>8); // (8bits mas bajos, porque los primeros 4 son reservados)
        puerto_serial->UBRR0L = (unsigned char)BAUD_PRESCALE;

        puerto_serial->status_control_b = (1<<RXEN0)|(1<<TXEN0);
        /* Set frame format: 8data, 2stop bit */
        puerto_serial->status_control_c = (1<<USBS0)|(3<<UCSZ00);
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
    while(!(    puerto_serial->status_control_a & (1<<UDREn)))
    ;
    puerto_serial->data_es = c;
    
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
    while(!(    puerto_serial->status_control_a & (1<<RXCn)))
    ;
    
    return  puerto_serial->data_es; //return valor en registro de datos e/s
}