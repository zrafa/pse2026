#include "timer.h"
#include "adc.h"
#include <math.h>
#include <stdint.h>

void main(){

    init_timer();
    adc_init();

    uint16_t val;
    uint16_t anterior_val = 0;
    double aux_d;

    while(1)
    {
        /* obtener una conversión ADC desde el pin de entrada ADC 2 */
        val = adc_get(2);

        aux_d = pow((double) val / 1023, (double) (1.0/3.14));

        val = (uint16_t) (aux_d * 1023);
	if(val != anterior_val)
	{
		cambiar_tope(val);
		anterior_val = val;
	}

    }
}
