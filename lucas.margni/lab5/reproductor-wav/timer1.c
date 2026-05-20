/* Driver del timer2 del atmega328p
 *
 * Interrupciones a frecuencia 11025 hz
 * Aproximadamente 0.0000907 interrupciones por segundo
 * Es decir, 90.7 interrupciones por microsegundo
 *
 * Modo Fast PWA
 *
 * Reloj del sistema: 16000000 ticks/s
 * Preescalar: 64
 * 
 * 16 ticks/us / 1 = 16 ticks/us
 * 16 ticks/us * 90.7 interrupciones/us = 1451
 * 
 * Valor de TOP: 1451 (por la cuenta de arriba)
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include "timer1.h"

volatile uint16_t ticks = 0;

/* Estructura de datos del driver timer1 */
typedef struct {
    uint8_t tccr1a;     /* Timer Control Register A */
    uint8_t tccr1b;     /* Timer Control Register B */
    uint8_t tccr1c;     /* Timer Control Register C */
    uint8_t reserved;
    uint8_t tcnt1l;     /* Timer Register Low */
    uint8_t tcnt1h;     /* Timer Register High */
    uint8_t icr1l;      /* Input Capture Register Low */
    uint8_t icr1h;      /* Input Capture Register High */
    uint8_t ocr1al;     /* Output Compare Register A Low */
    uint8_t ocr1ah;     /* Output Compare Register A High */
    uint8_t ocr1bl;     /* Output Compare Register B Low */
    uint8_t ocr1bh;     /* Output Compare Register B High */
} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *) 0x80;

/* Interrupt Mask Register */
volatile uint8_t *timer1_timsk1 = (uint8_t *) 0x6f;

/* Registros de control de pines */
volatile uint8_t *ddr_b = (unsigned char *) 0x24;

/* Inicializar driver timer1 */
void timer1_init() {
    /* configurar pines de salida */
    *ddr_b |= 1 << 1; /* OC1A */

    /* modo Fast PWM (14) */
    timer1->tccr1a |= 0x02;
    timer1->tccr1b |= 0x18;

    /* OC1A prendido desde bottom hasta llegar a OCR1A */
    timer1->tccr1a |= 0x80;

    /* preesacalar = 1 */
    timer1->tccr1b |= 0x01;

    /* TOP guardado en ICR1 (1451 = 0x05ab)*/
    timer1->icr1h = 0x05;
    timer1->icr1l = 0xab;

    /* genera interrupcion si contador es igual a OCR1A */
    *timer1_timsk1 |= 0x02;
}

ISR(TIMER1_COMPA_vect) {
    ticks++;
}

/* Modifica el registro comparador a */
void timer1_set_comparador(uint16_t valor) {
    /* tiempo de trabajo */
    timer1->ocr1ah = (valor >> 8) & 0x00ff;
    timer1->ocr1al = valor & 0x00ff;
}