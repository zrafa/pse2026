/*
delay_ms() (por software sin avr libc),
ADC: adc_init, adc_get
Agregar al driver ADC una funcion de configuración que permita (o en el init):
- elegir el comparador de tensión a 5v (vcc)
- elegir el comparador a otro voltage interno (creo que era 1v)
- elegir el comparador con una señal externa de voltage
ultrasound get()
*/

/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

/* Estructura de datos del driver ADC */

typedef struct {
	uint8_t adcl; /* ADC Data Register Low */
	uint8_t adch; /* ADCH — ADC Data Register High */
	uint8_t status_control_a;
	uint8_t status_control_b;
	uint8_t admux;
	uint8_t reservado;
	uint8_t didr0;
} volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78; /* direccion del primer registro */

void adc_init(uint8_t mode)
{
	/* Mode 1 = VCC */
	/* Mode 2 = 1V */
	/* Mode 3 = senal externa */
	adc->status_control_a |= (1 << ADEN); /* Habilitamos el ADC */

	switch (mode) {
	case 1:
		adc->admux |= (1 << REFS0);
		adc->admux &= ~(1 << REFS1);
		break;
	case 2:
		adc->admux |= (1 << REFS0);
		adc->admux |= (1 << REFS1);
		break;
	case 3:
		adc->admux &= ~(1 << REFS0);
		adc->admux &= ~(1 << REFS1);

		break;

	default:
		printf("Error");
		break;
	}

	/* Establecer tambien el preescalar para lograr un valor acorde (divisor) */
	adc->status_control_a |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

uint16_t adc_get(uint8_t pin)
{

	if (pin > 8 || pin < 0) {
		return -1;
	}

	/* 1. Selects which analog pin is connected to the ADC */

	adc->admux |= pin;
	adc->admux &= (pin | 0b11110000);
	/* 2. Write this bit to one to start each conversion */

	adc->status_control_a |= (1 << ADSC);

	/* 3. When conversion is complete, it returns to zero */

	while (adc->status_control_a && ((1 << ADSC)))
		;

	/* 4. When conversion is complete, read the data register */
	/* IMPORTANT: ADCL must be read first, then ADCH */

	uint16_t data = adc->adcl;
	data += ((adc->adch) & (0b00000011)) * 256;

	return data;
}
