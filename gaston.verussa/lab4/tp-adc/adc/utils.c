/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include "utils.h"

/* Estructura de datos del driver ADC */

void delay_ms(int ms)
{
	volatile int i;
	volatile int j;
	for(i = 0; i < ms; i++)
	{
		for(j = 0; j < 452; j++);
	}
}
