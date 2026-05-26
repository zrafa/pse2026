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

unsigned int notas[8] =
{262, 294, 330, 350, 392, 440, 494, 524};


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

void tocar_nota(char nota, int duracion){
	if(nota <= 7)
	{
		volatile unsigned long frecuencia = notas[nota];
		volatile unsigned long us_ciclo = 1000000UL / frecuencia;
		volatile unsigned long us_alto_bajo =  us_ciclo / 2UL;
		volatile unsigned long ciclos_en_duracion = (duracion * 1000UL) / us_ciclo;
		volatile unsigned long i;

		for(i = 0; i < ciclos_en_duracion; i++)
		{
			prender_piezo();
			_delay_us(us_alto_bajo);
			apagar_piezo();
			_delay_us(us_alto_bajo);
		}
	}
}

void silencio(int duracion_ms){
	volatile unsigned long j = duracion_ms * 1000UL;
	_delay_us(j);
}
