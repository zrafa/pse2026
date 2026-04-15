
/* utils.c - funciones de soporte al programa principal */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#define PIN_SOUND 0
#define TRIG 1
#define ECHO 2

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDRB (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PINB (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

/* melody_init: configura el puertos de salida */
void vehiculo_init() {
	// SPEAKER - SALIDA
	*ddr_b |= 1 << PIN_SOUND;

	// (TRIG) - SALIDA
	*ddr_b |= 1 << TRIG;

	// pin c, bit 5 (ECHO) - ENTRADA
	*ddr_b &= ~(1 << ECHO);
}

void disparo() {
	// poner señal de trig en alto
	*puerto_b |= 1 << TRIG;

	// espera de 10 us para el disparo
	_delay_us(10);

	// poner señal de trig en bajo
	*puerto_b &= ~(1 << TRIG);
}

/* ultrasound_get_distance()
 * 	devuelve la distancia en cm del objeto delante del sensor
 * 	devuelve -1 si no existe ningun objeto
 */
int ultrasound_get_distance(void) {
	volatile int dist = -1;
	volatile unsigned long int tiempo = 0;
	volatile char senial_alta = 0;

	disparo();

	// esperamos a que el echo suba la señal
	while(!senial_alta) {
		senial_alta = (*pin_b >> ECHO) & 1;
	}

	while(senial_alta && tiempo < 38000) {
		// escuchar cada 1 microsegundo
		_delay_us(1);
		tiempo++;

		// revisamos si el echo sigue teniendo la señal alta
		senial_alta = (*pin_b >> ECHO) & 1;
	}

	if(!senial_alta) {
		// no hubo timeout
		// se modifica la cuenta para calibrar
		dist = tiempo / 14.5;
		// equivalente a:
		//dist = tiempo / 58;
		//dist *= 4;
	}

	return dist;
}

volatile unsigned int sonido_us = 478;

void silencio(unsigned long espera) {
	_delay_us(espera);
}

void reproducir_pitido() {
	// calculamos cuantos periodos hay en un cuarto de segundo para la nota dada
	volatile unsigned long cant_rep = 250000UL / sonido_us;
	volatile unsigned long i;

	volatile unsigned long medio_periodo = sonido_us / 2;

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
}