/* Driver del timer2 del atmega328p
 *
 * Genera 1000 interrupciones por segundo
 *
 * Modo Fast PWM
 *
 * Reloj del sistema: 16000000 ticks/s
 * Preescalar: 64
 *
 * 16000000 ticks/s / 64 = 250000 ticks/s
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include "timer2.h"

volatile uint16_t ticks = 0;

/* Estructura de datos del driver timer2 */
typedef struct {
    uint8_t tccr2a; /* Timer Control Register A */
    uint8_t tccr2b; /* Timer Control Register B */
    uint8_t tcnt2;  /* Timer Register */
    uint8_t ocr2a;  /* Output Compare Register A */
    uint8_t ocr2b;  /* Output Compare Register B */
} volatile timer2_t;

volatile timer2_t *timer2 = (timer2_t *) 0xb0;

/* Interrupt Mask Register */
volatile uint8_t *timer2_timsk2 = (uint8_t *) 0x70;

/* Registros de control de pines */
volatile uint8_t *ddr_b = (unsigned char *) 0x24;
volatile uint8_t *ddr_d = (unsigned char *) 0x2a;

/* Inicializar driver timer2 */
void timer2_init() {
    /* configurar pines de salida */
    *ddr_b |= 1 << 3; /* oc2a */
    *ddr_d |= 1 << 3; /* oc2b */

    /* modo Fast PWM */
    timer2->tccr2a |= 0x03;

    /* oc2a prendido desde bottom hasta llegar a OCR2A */
    timer2->tccr2a |= 0x80;
    /* oc2a prendido desde bottom hasta llegar a OCR2B */
    timer2->tccr2a |= 0x20;

    /* preesacalar = 64 */
    timer2->tccr2b |= 0x04;

    /* genera interrupcion si contador es igual a OCR2A */
    (*timer2_timsk2) |= 0x02;
}

/* Rutina de atencion de interrupciones */
ISR(TIMER2_COMPA_vect) {
    ticks++;
}

/* Devolver la cantidad de ticks actuales */
uint16_t timer2_get_ticks() {
    return ticks;
}

/* Modifica los registros comparadores */
void timer2_set_comparadores(uint8_t valor) {
    /* tiempo de trabajo */
    timer2->ocr2a = valor;
    timer2->ocr2b = valor;
}