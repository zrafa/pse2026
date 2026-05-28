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

typedef struct
{
    uint8_t adcl;   /* 0x78 - ADC Data Register Low */
    uint8_t adch;   /* 0x79 - ADC Data Register High */
    uint8_t adcsra; /* 0x7A - ADC Control and Status Register A */
    uint8_t adcsrb; /* 0x7B - ADC Control and Status Register B */
    uint8_t admux;  /* 0x7C - ADC Multiplexer Selection Register */
} volatile adc_t;

volatile adc_t *adc = (adc_t *) 0x78;


void adc_init()
{
 // Primer bit encender adc
 adc->admux = 0b01000000;
 // Ultimos 3 bits preescalar, factor de divisior 128
 adc->adcsra = adc->adcsra | 0b10000111;

}

int adc_get(char input)
{
        /* 1. Selects which analog input is connected to the ADC */
  adc->admux = (adc->admux & 0xF0) | (input & 0x0F);//primeros 4 son configuracion y los otros son el input
        /* 2. Write this bit to one to start each conversion */
adc->adcsra |= 0b01000000;
        /* 3. When conversion is complete, it returns to zero */
 while (adc->adcsra & 0b01000000) {  }
        /* 4. When conversion is complete, read the data register */
        /* IMPORTANT: ADCL must be read first, then ADCH */
 uint8_t low_byte = adc->adcl; //para desbloquear
 uint8_t high_byte = adc->adch; //para sacar el dato
	/* return the value */

 return high_byte;// por que usamos 8 bits de resolucion
  return 0;
}
