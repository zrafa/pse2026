#include <avr/io.h>

void timer2_init_pwm(void) {
    // 1. Configurar los pines correspondientes al Timer2 como salida
    // OC2A corresponde a PB3 (Pin digital 11)
    // OC2B corresponde a PD3 (Pin digital 3)
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD3);

    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

    TCCR2B = (1 << CS22);

    OCR2A = 0;
    OCR2B = 0;
}

void timer2_set_duty(uint8_t duty) {
    OCR2A = duty;  // Actualiza PWM en el pin 11
    OCR2B = duty;  // Actualiza PWM en el pin 3
}