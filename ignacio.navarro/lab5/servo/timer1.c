#include <avr/io.h>
#include "timer1.h"
#include "serial.h"

void timer1_init() {
    serial_init();

    // D9 como salida
    DDRB |= (1 << PB1);

    // TCCR1A:
    // COM1A1 = 1 clear on match, non-inverting
    // WGM11 = 1 modo 14
    TCCR1A = (1 << COM1A1) | (1 << WGM11);

    // TCCR1B:
    // WGM13 = 1, WGM12 = 1 modo 14 fast PWM con TOP en ICR1
    // CS11 = 1 preescalar de 8
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);

    // cambiar TOP para 50Hz (20ms)
    ICR1 = 40000;

    // pos inicial 90 grados
    OCR1A = 3000;
}

void servo_set_angle(uint16_t adc_val) {
    // mapeo ADC 0 - 1023 a OCR1A 2000 - 4000
    uint32_t duty = 2000 + ((uint32_t)adc_val * 2000 / 1023);

    OCR1A = (uint16_t)duty;
}