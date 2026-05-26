#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "timer1.h"


int main()
{
	float val;
	unsigned int valor_timer;

	adc_init();
	timer1_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		// Linealiza el valor
		val = val / 1024.0;
		val = pow(val, 0.25) * 1000.0;

		//Redondeamos el valor y lo pasamos a un valor entre 1000 y 2000 para setear el tiempo de trabajo
		valor_timer = (unsigned int)(floor(val) + 1000);

		timer1_setvalor(valor_timer);

		//Damos un tiempo de delay para que el servo pueda moverse a la posición dada por el valor del ADC
		_delay_us(1000000UL);
	}

	for(;;);
}
