#include "timer.h"
#include "adc.h"
#include <math.h>

void main()
{

    init_timer();
    adc_init();

    char val;
    char anterior_val = 0;
    int adc;
    double aux_d;

    while (1)
    {
        /* obtener una conversión ADC desde el pin de entrada ADC 2 */
        adc = adc_get(2);

        aux_d = pow((double)adc / 1023, (double)(1.0 / 3.14));

        adc = (int)(aux_d * 255);
        val = (char)adc;
        if (val != anterior_val)
        {
            cambiar_tope(val);
            anterior_val = val;
        }
    }
}
