#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <stdint.h>
#include "adc.h"

void timer2_init_pwm(void);
void timer2_set_duty(uint8_t duty);

int main(void) {
    // Inicializar
    adc_init();
    timer2_init_pwm();

    while (1) {
        
        uint8_t val_adc = adc_get(0);

        timer2_set_duty(val_adc);

        _delay_ms(15);
    }
    
    return 0;
}