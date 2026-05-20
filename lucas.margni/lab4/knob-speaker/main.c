#include "adc.h"
#include "speaker.h"
#include "serial.h"

#include <math.h>

void main() {
	float val;

	adc_init();
	speaker_init();

	while (1) {
		/* obtener una conversión ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* linealizar el valor dado */
		val = val / 1024.0;
		val = pow(val, 0.3) * 1024;

		/* se reproduce una nota distinta dependiendo de lo recibido por el knob */
		reproducir_nota((int)round(val * 2), 10);
	}
}