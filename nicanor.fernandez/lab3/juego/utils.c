
/* utils.c - funciones de soporte al programa principal */

/* puertos de E/S */
#include "serial.h"

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDRB (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PINB (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;



/* led_init: configura el puertos de entrada y salida */
void led_init() {
	//Registro b, bit 0, bit 1,  bit 2 y bit 3 - ENTRADA
	*ddr_b &= ~((1 << 0 | 1 << 1 | 1 << 2 | 1 << 3));

	//Activamos el pull-up en todos
	*puerto_b |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;
}


void verificar_caracter() {
	// verificamos si se presionó uno de los pulsadores

	if(!(*pin_b & 1)) {
		//Si está activo el bit 0 enviamos 'd' (nos movemos a la izquierda)
		serial_put_char('d');
	} else if(!(*pin_b & 2)) {
		//Si está activo el bit 1 enviamos 'a' (nos movemos a la derecha)
		serial_put_char('a');
	} else if(!(*pin_b & 4)){
		//Si está activo el bit 2 enviamos ' ' (disparamos)
		serial_put_char(' ');
	} else if(!(*pin_b & 8)) {
		//Si está activo el bit 3 enviamos 'q' (salimos del juego)
		serial_put_char('q');
	}
	//Realizamos una espera para evitar problemas por las oscilaciones que genera el pulsador
	_delay_us(100000);
}