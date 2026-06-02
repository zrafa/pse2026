#include <util/delay.h>
#include "timer.h"
#include "adc.h"
#include <math.h>
#include <stdint.h>

void main(){

    init_timer();
    adc_init();

    uint16_t adc;
    uint16_t val_timer;

    while(1){

        adc = adc_get(2); // Puerto 2

        /*
        aux_d = pow((double)adc / 1023, (double)(1.0 / 3.14));

        adc = (int)(aux_d * 255);
        val = (char)adc;
        if (val != anterior_val)
        {
            cambiar_tope(val);
            anterior_val = val;
        }
            */
           
        val_timer = 250 + (((uint32_t)adc * 250) / 1023);

        actualizar_servo(val_timer);

        _delay_ms(15);

    }
}