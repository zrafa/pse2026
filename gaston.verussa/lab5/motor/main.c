#include "timer.h"
#include "adc.h"
#include <math.h>

void main(){

    init_timer();
    adc_init();

    char val;
    char anterior_val = 0;
    int aux_i;
    double aux_d;

    while(1)
    {
        /* obtener una conversión ADC desde el pin de entrada ADC 2 */
        aux_i = adc_get(2);

        aux_d = pow((double) aux_i / 1023, (double) (1.0/3.14));

        aux_i = (int) (aux_d * 255);
        val = (char) aux_i;
	if(val != anterior_val)
	{
		cambiar_tope(val);
		anterior_val = val;
	}

    }
}
