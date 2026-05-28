/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> 
#include "adc.h"

#define REFS0 6    /* ADMUX: Reference Selection */
#define ADEN  7    /* ADCSRA: ADC Enable */
#define ADSC  6    /* ADCSRA: ADC Start Conversion */
#define ADPS2 2    /* ADCSRA: Prescaler bits */
#define ADPS1 1
#define ADPS0 0



typedef struct
{
  uint8_t adcl;       /* 0x78: ADC Data Register Low */
  uint8_t adch;       /* 0x79: ADC Data Register High */
  uint8_t adcsra;     /* 0x7A: ADC Control and Status Register A */
  uint8_t adcsrb;     /* 0x7B: ADC Control and Status Register B */
  uint8_t admux;      /* 0x7C: ADC Multiplexer Selection Register */
  uint8_t reserved;   /* 0x7D: Espacio reservado */
  uint8_t didr0;      /* 0x7E: Digital Input Disable Register */
} volatile adc_t;

volatile adc_t *adc = (adc_t *) 0x78; /* direccion del primer registro */

void adc_init()
{
  adc->admux = (1 << REFS0);

  adc->adcsra = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int adc_get(char input)
{
 
  adc->admux = (adc->admux & 0xF0) | (input & 0x07);

  
  adc->adcsra |= (1 << ADSC);

 
  while (adc->adcsra & (1 << ADSC)) {
    // espera activa
  }
  
  uint8_t low  = adc->adcl;
  uint8_t high = adc->adch;

  
  return (int)((high << 8) | low);
}
