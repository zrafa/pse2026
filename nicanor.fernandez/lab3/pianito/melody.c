
/* utils.c - funciones de soporte al programa principal */

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

/* melody_init: configura el puertos de salida */
void melody_init() {
	// registro b, bit 0
	*ddr_b |= 1 << PIN_SOUND;
}

// guardamos el tiempo en microsegundos de un periodo para cada nota
volatile unsigned int us_notas[] = {478, 426, 379, 358, 319, 284, 253}; // septima
// volatile unsigned long us_notas[] = {3822, 3405, 3033, 2863, 2551, 2273, 2025}; // cuarta

/* reproducir_nota: 0 do, 1 re, 2 mi, 3 fa, 4 sol, 5 la, 6 si (por un segundo) */
void reproducir_nota(char nota) {
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
	// un segundo que no se escucha nada
	_delay_us(500000);

	// delay para diferenciar notas
	_delay_us(10000);
}