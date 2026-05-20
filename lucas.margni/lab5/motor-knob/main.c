#include <avr/interrupt.h>

#include "timer2.h"
#include "adc.h"

#include <math.h>

void main() {

	timer2_init();
	adc_init();

	/* habilitar las interrupciones a nivel global */
    sei();

	float val;
	unsigned char val_timer;

	while (1) {
		/* obtener una conversion ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* linealizar el valor dado */
		val = val / 1024.0;
		val = pow(val, 0.3) * 1024.0;

		/* se redondea y se reduce a 8 bits (0 a 255) */
		val_timer = (unsigned char)(floor(val) / 4);

		/* se actualiza el tiempo de trabajo */
		timer2_set_comparadores(val_timer);
	}
}