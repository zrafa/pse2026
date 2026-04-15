
/* utils.c - funciones de soporte al programa principal */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328p
 * El puerto B de un atmega328p tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#define PB0 0

#include <avr/io.h>
#include <util/delay.h>

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;


/* piezo_init: configura el puerto b como salida */
void piezo_init() {
	*ddr_b |= (1 << PB0);
}

void prender_piezo(){
	*puerto_b |= (1 << PB0);
}

void apagar_piezo(){
	*puerto_b &= ~(1 << PB0);
}

void tocar_nota(int frecuencia, int duracion){
	volatile unsigned long us_ciclo = 1000000UL / frecuencia; //Duracion de cada ciclo en ms
	volatile unsigned long us_alto_bajo =  us_ciclo / 2UL; //alto y bajo duran medio ciclo
	volatile unsigned long ciclos_en_duracion = (duracion * 1000UL) / us_ciclo; // cuantos ciclos hay en la duracion del sonido
	volatile unsigned long i;

	for(i = 0; i < ciclos_en_duracion; i++)
	{
		prender_piezo();
		_delay_us(us_alto_bajo);
		apagar_piezo();
		_delay_us(us_alto_bajo);
	}
	// Delay agregado entre nota y nota, fijo por la cancion
	_delay_us(400000);
}
