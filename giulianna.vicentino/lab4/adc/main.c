
#include "adc.h"

main()
{
	int val;

	adc_init()

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_read(2);

		/* realizar alguna acción con val */

		delay_ms(500);
	}

	for(;;);
}
