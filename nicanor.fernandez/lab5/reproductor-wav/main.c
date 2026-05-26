#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "timer1.h"


int main()
{
	unsigned char dato;
	unsigned int valor_enviado;

	serial_init();
	timer1_init();

	//Activamos las interrupciones globales
	sei();

	while (1) {
		//Obtenemos el dato a reproducir por el serial 
 		dato = serial_get_char(); //Recibe un dato entre 0 y 255

		//El máximo valor que se le da al timer para establecer correctamente el tiempo de trabajo es 1451 (interrupciones por microsegundo) / 5 (para establecer la escala a 1V) = 290.
		/* El dato que se envía al timer es proporcional al dato que se recibe por el serial
			255 recibidos = 290 enviados (máximo tiempo de trabajo)
			dato recibido = valor_enviado * 290 / 255
		*/
		valor_enviado = (unsigned int) dato * 290 / 255;


		//Seteamos el tope del timer
		timer1_setvalor(valor_enviado);
	}

	for(;;);
}
