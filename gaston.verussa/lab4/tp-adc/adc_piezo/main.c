
#include "adc.h"
#include "speaker.h"
#include "serial.h"

void main()
{

	adc_init();
	piezo_init();
	serial_init();

	int val;
	char nota;

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);
		nota = (char) (val >> 7); // tomamos los primeros 3 bits (considerando 10)

		serial_put_char(nota);
		tocar_nota(nota,100);
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
	}

	for(;;);
}
