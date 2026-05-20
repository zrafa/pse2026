
#include "adc.h"
#include "utils.h"
#include "serial.h"

void main()
{

	adc_init();
	serial_init();

	int val;
	char cero = '0';

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		serial_put_char((char) (val/256));
		serial_put_char((char) (val%256));
		/* realizar alguna acción con val */
		/*
		serial_put_char(cero + (char) val/1000);
		serial_put_char(cero + (char) (val/100) % 10);
		serial_put_char(cero + (char) (val/10) % 10);
		serial_put_char(cero + (char) val%10);
		
		serial_put_char('x');
		serial_put_char('x');
		serial_put_char('x');
		*/
		delay_ms(5000);
	}

	for(;;);
}
