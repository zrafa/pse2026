#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#include "timer1.h"
#include "adc.h"

#include <math.h>

void main() {

	timer1_init();
	adc_init();

	float val;
	unsigned int val_timer;

	while (1) {
		/* obtener una conversion ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* linealizar el valor dado */
		val = val / 1024.0;
		val = pow(val, 0.25) * 1000.0;

		/* se redondea y se pasa para que sea un valor entre 1000 y 2000 */
		val_timer = (unsigned int)(floor(val)) + 1000;

		/* 20000 us -> 5000, val_timer us -> ? (entre 250 y 500) */
		// val_timer = val_timer * 5000 / 20000;
		val_timer = (unsigned int)(val_timer / 4);

		/* se actualiza el tiempo de trabajo */
		timer1_set_comparador(val_timer);

		_delay_us(1000000UL);
	}
}