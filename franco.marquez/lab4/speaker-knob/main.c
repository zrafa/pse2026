#include "adc.h"
#include "knob.h"
#include "serial.h"

void main()
{

    //Inicio los drivers
	adc_init();
	piezo_init();
	serial_init();

	int val;
	char nota;

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2); //Puerto 2

		nota = (char) (val >> 7); // tomamos los primeros 3 bits (considerando 10)

		serial_put_char(nota);
		tocar_nota(nota,100);

	}

	for(;;);
}
