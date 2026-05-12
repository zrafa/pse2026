
#include "adc.h"
#include <stdlib.h>


int main()
{
	int val;

	adc_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		serial_put_char(val);
		/* realizar alguna acción con val */
		printf("Valor:%i",val);
		
		//system("sudo brightnessctl set %d")
		
		delay_ms(500);
	}

	for(;;);

	return 0;
}
