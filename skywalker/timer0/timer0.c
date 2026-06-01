/* timer0.c - Driver del timer 0 del atmega328p
 * 
 * META: ocultar el hardware a la aplicacion 
 *
 * USO:
 */

#include "timer0.h"
#include <stdint.h>

typedef struct {
	uint8_t tccr0a;     /* Timer Control Register A */
	uint8_t tccr0b;     /* Timer Control Register B */
	uint8_t tcnt0;      /* Timer Register */
	uint8_t ocr0a;      /* Output Compare Register A */
	uint8_t ocr0b;      /* Output Compare Register B */
} volatile timer0_t;

volatile timer0_t *timer0 = (timer2_t *) 0x44;

/* Interrupt Mask Register */
volatile uint8_t *timer0_timsk0 = (uint8_t *) 0x6e;

volatile uint8_t value = 0;

/* Rutina de atencion de interrupciones */
ISR(TIMER0_COMPA_vect)
{
    value++;
}

/* Configura el modo y el prescalar del timer
 * Modo CTC o Fast PWM, ambos con tope OCR0A
 * Devuelve -1 si el modo o el prescalar es invalido y 0 en otro caso
 */
int8_t timer0_init(uint8_t mode, uint8_t prescaler, uint8_t initial_top)
{
	if (mode > 1 || prescaler > 4)
		return -1;

	if (mode == MODE_CTC) {
		timer0->tccr0a |= (1 << 1);
		timer0->tccr0a &= ~(1 << 0);
		timer0->tccr0b &= ~(1 << 3);
	} else { /* mode == MODE_PWM */
		timer0->tccr0a |= (1 << 1 | 1 << 0);
		timer0->tccr0b |= (1 << 3);
	}

        switch (prescaler) {
		case PRESCALER_1:
                        timer0->tccr0b |= (1 << 0);
			timer0->tccr0b &= ~(1 << 2 | 1 << 1);
                        break;
			
		case PRESCALER_8:
                        timer0->tccr0b |= (1 << 1);
			timer0->tccr0b &= ~(1 << 2 | 1 << 0);
                        break;

		case PRESCALER_64:
			timer0->tccr0b |= (1 << 1 | 1 << 0);
			timer0->tccr0b &= ~(1 << 2);
                        break;

		case PRESCALER_256:
                        timer0->tccr0b |= (1 << 2);
			timer0->tccr0b &= ~(1 << 1 | 1 << 0);
                        break;

		case PRESCALER_1024:
                        timer0->tccr0b |= (1 << 2 | 1 << 0);
			timer0->tccr0b &= ~(1 << 1);
                        break;
	}

	timer0->ocr0a = initial_top;

	return 0;
}

/* Modifica el valor del contador pasado
 * Devuelve -1 si el contador es invalido y 0 en otro caso
 */
int8_t timer0_set_counter(uint8_t counter, uint8_t new_value)
{
	if (counter > 1)
		return -1;

	if (counter == COUNTER_A)
		timer0->ocr0a = new_value;
	else /* counter == COUNTER_B */
		timer0->ocr0b = new_value;

        return 0;
}

/* Obtiene el valor del timer
 */
uint8_t timer0_get_value()
{
        return value;
}

/* Habilita las interrupciones del contador pasado
 * Devuelve -1 si el contador es invalido y 0 en otro caso
 */
int8_t timer0_enable_interrupts(uint8_t counter)
{
	if (counter > 1)
		return -1;

	if (counter == COUNTER_A)
		*timer0_timsk0 |= (1 << 1);
	else /* counter == COUNTER_B */
		*timer0_timsk0 |= (1 << 2);

	return 0;
}

/* Deshabilita las interrupciones del contador pasado
 * Devuelve -1 si el contador es invalido y 0 en otro caso
 */
int8_t timer0_disable_interrupts(uint8_t counter)
{
        if (counter > 1)
		return -1;

        if (counter == COUNTER_A)
                *timer0_timsk0 &= ~(1 << 1);
	else /* counter == COUNTER_B */
                *timer0_timsk0 &= ~(1 << 2);

        return 0;
}