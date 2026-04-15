/*
 * ultrasound: controla el sensor HC-SR04 para medir distancias en cm
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>

#define TRIG 4
#define ECHO 5

/* direccion de PORTC (registro de datos) */
volatile unsigned char * puerto_c = (unsigned char *) 0x28;

/* direccion de DDRC (registro de control) */
volatile unsigned char * ddr_c = (unsigned char *) 0x27;

/* direccion PINC (registro de datos de entrada) */
volatile unsigned char * pin_c = (unsigned char *) 0x26;

void ultrasonido_init() {
	// pin c, bit 4 (TRIG) - SALIDA
	*ddr_c |= 1 << TRIG;

	// pin c, bit 5 (ECHO) - ENTRADA
	*ddr_c &= ~(1 << ECHO);
}

void disparo() {
	// poner señal de trig en alto
	*puerto_c |= 1 << TRIG;

	// espera de 10 us para el disparo
	_delay_us(10);

	// poner señal de trig en bajo
	*puerto_c &= ~(1 << TRIG);
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
		senial_alta = (*pin_c >> ECHO) & 1;
	}

	while(senial_alta && tiempo < 38000) {
		// escuchar cada 1 microsegundo
		_delay_us(1);
		tiempo++;

		// revisamos si el echo sigue teniendo la señal alta
		senial_alta = (*pin_c >> ECHO) & 1;
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