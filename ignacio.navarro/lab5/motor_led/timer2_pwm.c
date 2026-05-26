#include <avr/io.h>
#include "timer2_pwm.h"

typedef struct {
    uint8_t tccr2a;
    uint8_t tccr2b;
    uint8_t tcnt2;
    uint8_t ocr2a;
    uint8_t ocr2b;
} volatile timer2_t;

timer2_t *tmr2 = (timer2_t *) 0xB0;

void timer2_pwm_init() {
    // D11 (PB3) y D3 (PD3) como salida
    DDRB |= (1 << PB3); // OC2A
    DDRD |= (1 << PD3); // OC2B

    // TCCR2A 
    // COM2A1=1, COM2B1=1 modo no invertido para motor y led
    // WGM21=1, WGM20=1 fast pwm
    tmr2->tccr2a = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

    // TCCR2B
    // CS22=1 preescalar en 64
    tmr2->tccr2b = (1 << CS22);

    tmr2->ocr2a = 0;
    tmr2->ocr2b = 0;
}

void timer2_set_pwm(uint8_t duty_a, uint8_t duty_b) {
    tmr2->ocr2a = duty_a;
    tmr2->ocr2b = duty_b;
}