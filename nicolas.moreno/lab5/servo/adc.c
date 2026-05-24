#include <stdint.h>
#include "adc.h"

typedef struct
{
uint8_t adcl;  
uint8_t adch; 
uint8_t adcsra; 
uint8_t adcsrb; 
uint8_t admux; 
uint8_t reserved; 
uint8_t didr0;  
} volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78;

void adc_init()
{
    /* AVCC con capacitor externo (01) en los bits 7 y 6 */
    adc->admux = 0b01000000;
    
    /* ADEN=1 (Encender), ADPS=111 (Prescaler 128) */
    adc->adcsra = 0b10000111;
}

int adc_get(char input)
{
    /* Configuramos: AVCC (01), ADLAR=1 (1) para leer 8 bits, y el Canal (input) */
    adc->admux = 0b01100000 | (input & 0x0F);

    /* Iniciar conversión (ADSC = bit 6) */
    adc->adcsra |= 0b01000000;
    
    /* Esperar a que termine la conversión */
    while (adc->adcsra & 0b01000000);
    
    /* Como configuramos ADLAR=1, el resultado de 8 bits está directo en ADCH */
    return adc->adch;
}