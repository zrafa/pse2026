#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "timer2.h"


int main()
{
	float val;

	adc_init();
	timer2_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		// Linealiza el valor
		val = val / 1024.0;
		val = pow(val, 0.3) * 1024.0;

		timer2_setvalor((int)(val/4));
	}

	for(;;);
}
