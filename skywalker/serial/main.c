#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

int main(void)
{
	
	serial_init(9600, 1);

	serial_put_str("int: ");
	serial_put_int(12345);

    serial_put_str("\r\n");

	serial_put_str("float: ");
	serial_put_float(31.45);


	/* Prueba de Recepción (RX) por interrupciones */
	while (1) {
        
		char recibido = serial_get_char_buffered();
		
		serial_put_str("letra: ");
		serial_put_char(recibido);
		serial_put_str("\r\n");

        _delay_ms(1000);
	}

	return 0;
}