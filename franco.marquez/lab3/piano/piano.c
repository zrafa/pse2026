#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#define PIN_SOUND 0

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDRB (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PINB (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

void speaker_init() {
	
	*ddr_b |= 1 << PIN_SOUND;
}

// tiempo de una nota en Sexta
volatile unsigned int us_notas[] = {955, 850, 757, 715, 637, 567, 505}; 

void tocar_nota(char nota) {
	// calculamos cuantos periodos hay en medio segundo para la nota dada
	volatile unsigned long cant_rep = 500000UL / us_notas[nota];
	volatile unsigned long i;

	volatile unsigned long medio_periodo = us_notas[nota] / 2;

	for(i = 0; i < cant_rep; i++) {
		// reproducimos un periodo

		// poner en alto la señal
		*puerto_b |= 1 << PIN_SOUND;
		// esperamos
		_delay_us(medio_periodo);
		// poner en bajo la señal
		*puerto_b &= ~(1 << PIN_SOUND);
		// esperamos
		_delay_us(medio_periodo);
	}

	// delay para diferenciar notas
	_delay_us(10000);
}

void silencio() {

	_delay_us(500000);

	_delay_us(10000);
}