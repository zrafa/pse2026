#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>

#include "adc.h"
#include "utils.h"


int main()
{
	float val;

	adc_init();
	melody_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* realizar alguna acción con val */
		val = val / 1024.0;
		val = pow(val, 0.3) * 1024.0;

		int frecuencia = (int) round(val*3);

		reproducir_frecuencia(frecuencia);
	}

	for(;;);
}
