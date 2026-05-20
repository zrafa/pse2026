
#include "adc.h"
#include "utils.h"
#include "serial.h"
#include "math.h"

void main()
{
	adc_init();
	serial_init();

	int val;
	char cero = '0';
	double aux;

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		aux = pow((double) val / 1023, (double) (1.0/3.14));

		aux = aux * 1023;

		val = (int) aux;

		serial_put_int(val, 4);
		serial_put_char('\n');
		delay_ms(1500);
	}

	for(;;);
}
