/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include "adc.h"

#define REFS0 0x40
#define REFS1 0x80
#define ADEN  0x80
#define ADSC  0x40
/* Estructura de datos del driver ADC */

typedef struct
{
uint8_t adcl;  
uint8_t adch; 
uint8_t adcsra; /* ADC Control and Status Register A */
uint8_t adcsrb; 
uint8_t admux; /* ADC Multiplexer Selection Register */
uint8_t reserved; 
uint8_t didr0;  

} 
volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78;

void adc_init()
 {
    /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
    de vcc con capacitor externo y encender (habilitar) el periferico */

    adc->admux |= REFS0;
    adc->admux &= ~REFS1;   /* external  */
    adc->admux &= ~0b1111; /* adc0 */

    adc->admux |= 0b100000;

    adc->adcsra |=  ADEN;
    adc->adcsra |=  0b101;
    adc->adcsra &= ~0b010;

    /* Establecer tambien el prescalar para lograr un valor acorde (divisor) */
}
int adc_get(char input)
{
    /* Limpiamos los últimos 4 bits (MUX) y ponemos el canal que pediste */
    adc->admux = (adc->admux & 0xF0) | (input & 0x0F);

    /* Iniciar la conversión */
    adc->adcsra = adc->adcsra | 0b01000000;
    
    /* Esperar a que termine */
    while (adc->adcsra & 0b01000000);
        
    /* Leer datos (ADCL primero) */
    uint8_t low = adc->adcl;
    uint8_t high = adc->adch;
    
    return high; /* Devuelve un valor de 0 a 255 */
}