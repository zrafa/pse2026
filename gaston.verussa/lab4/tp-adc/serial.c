
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
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */

    uint8_t status_control_b;
    uint8_t status_control_c;
    uint8_t reservado;
    uint8_t ubrrL;
    uint8_t ubrrH;
    /* demas registros */

    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);


#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define PD0 0
#define PD1 1
#define RXEN0 4
#define TXEN0 3
#define UPM0 4
#define USBS0 3
#define UCSZ0 1
#define UCSZ2 2
#define UDRE0 5
#define RXC0 7

void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
	puerto_serial->ubrrH = (unsigned char) (BAUD_PRESCALE >> 8);
	puerto_serial->ubrrL = (unsigned char) BAUD_PRESCALE;


	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
	puerto_serial->status_control_b &= ~(1<<UCSZ2);
	puerto_serial->status_control_c |= (3<<UCSZ0);
	puerto_serial->status_control_c &= ~(1<<USBS0);
	puerto_serial->status_control_c &= ~(3<<UPM0);

	/* Activar la recepcion y transmicion */
	puerto_serial->status_control_b |= (1 <<RXEN0)|(1<<TXEN0);

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

	while(!(puerto_serial->status_control_a & (1<<UDRE0)));

    /* Send the character via the serial port. */

	puerto_serial->data_es = c;
    /* (escribir el dato al registro de datos de E/S */

}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utiliza	ndo el bit correcto */
    
    // while ( /* completar con E/S programada */ )
    //     ;

	while(!(puerto_serial->status_control_a & (1<<RXC0)));

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */

	return puerto_serial->data_es;
}



