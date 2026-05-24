#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include <stdint.h>
#include "adc.h"

void timer1_init_servo(void);
void timer1_set_servo(uint16_t duty);

int main(void) {
    // Inicializar periféricos
    adc_init();
    timer1_init_servo();

    while (1) {
        uint8_t val_adc = adc_get(2);

        // Mapeo lineal rápido:
        uint16_t pwm_val = 250 + val_adc;

        // Enviar la señal al servo
        timer1_set_servo(pwm_val);

        _delay_ms(15);
    }
    
    return 0;
}