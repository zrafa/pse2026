#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#include "adc.h"
#include "serial.h"


int main()
{
	int val;

	adc_init();
	serial_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* realizar alguna acción con val */
		serial_put_int(val, 4);
		serial_put_char('\n');

		_delay_ms(500);
	}

	for(;;);
}
