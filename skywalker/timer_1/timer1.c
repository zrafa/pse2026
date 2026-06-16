#include "timer1.h"
#include <stdint.h>

typedef struct {
	uint8_t tccr1a; /* 0x80 */
	uint8_t tccr1b;
	uint8_t tccr1c;
	uint8_t reserved;
	uint8_t tcnt1l;
	uint8_t tcnt1h;
	uint8_t icr1l;
	uint8_t icr1h;
	uint8_t ocr1al;
	uint8_t ocr1ah;
	uint8_t ocr1bl;
	uint8_t ocr1bh; /* 0x8B */
} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *)0x80;

volatile uint8_t *timsk1 = (uint8_t *)0x6f;

int8_t init_timer(uint8_t mode, uint8_t prescalar)
{
	if (mode > PWM || prescalar > PRESCALAR_EXTERNAL)
		return -1;
	/* Mode 1 = Normal */
	/* Mode 2 = PWM */
	*(volatile uint8_t *)0x24 |= (1 << 1);

	timer1->tccr1a = 0;
	timer1->tccr1b = 0;

	switch (mode) {
	case NORMAL:
		/* Necesita 4 pines en 0 */
		break;
	case PWM:
		timer1->tccr1a |= (1 << WGM11);
		timer1->tccr1b |= (1 << WGM13) | (1 << WGM12);

		/* Configurar el tope */
		timer1->icr1h = 0xFF;
		timer1->icr1l = 0xFF;

		/* Ciclo de trabajo */
		break;
	default:
		break;
	}

	/* Ajusta el preescalar o si es fuente externa */
	timer1->tccr1b |= prescalar;

	return 0;
}

uint16_t get_timer(void)
{
	uint8_t low = timer1->tcnt1l;
	uint8_t high = timer1->tcnt1h;

	return ((uint16_t)high << 8) | low;
}

int8_t configure_comparator(uint16_t value, uint8_t mode)
{
	if (mode != A && mode != B)
		return -1;
	
	/* primero high o primero low? */
	uint8_t byte_low = (uint8_t)(value & 0xFF);

	uint8_t byte_high = (uint8_t)(value >> 8);

	if (mode == A) {
		timer1->ocr1ah = byte_high;
		timer1->ocr1al = byte_low;
	} else if (mode == B) {
		timer1->ocr1bh = byte_high;
		timer1->ocr1bl = byte_low;
	}

	return 0;
}

void configure_top(uint16_t top)
{
	/* Ciclo de trabajo */
	uint8_t byte_high = (uint8_t)(top >> 8);
	uint8_t byte_low = (uint8_t)(top & 0xFF);

	timer1->icr1h = byte_high;
	timer1->icr1l = byte_low;
}
