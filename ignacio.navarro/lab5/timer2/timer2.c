#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer2.h"

/* Estructura Overlay para Timer2 */
typedef struct {
    uint8_t tccr2a;  /* 0xB0: Control Register A */
    uint8_t tccr2b;  /* 0xB1: Control Register B */
    uint8_t tcnt2;   /* 0xB2: Counter Register */
    uint8_t ocr2a;   /* 0xB3: Output Compare Register A */
    uint8_t ocr2b;   /* 0xB4: Output Compare Register B */
} volatile timer2_t;

/* Puntero al bloque de registros */
timer2_t *tmr2 = (timer2_t *) 0xB0;

/* El registro de máscara de interrupción está en 0x70 */
volatile uint8_t *timsk2 = (uint8_t *) 0x70;

// Variable global para los ticks (centésimas)
volatile uint32_t ticks_centis = 0;

void timer2_init() {
    /* 1. Modo CTC: WGM21=1, WGM20=0 (definido en TCCR2A) */
    tmr2->tccr2a = (1 << WGM21);

    /* 2. Valor de comparación para 10ms (156 pasos) */
    tmr2->ocr2a = 155;

    /* 3. Activar interrupción por comparación (OCIE2A) */
    *timsk2 |= (1 << OCIE2A);

    /* 4. Prescaler 1024 y arrancar: CS22=1, CS21=1, CS20=1 */
    tmr2->tccr2b = (1 << CS22) | (1 << CS21) | (1 << CS20);
    
    /* 5. Activar interrupciones globales */
    sei();
}

/* Rutina de Atención de Interrupción (ISR) */
ISR(TIMER2_COMPA_vect) {
    ticks_centis++;
}