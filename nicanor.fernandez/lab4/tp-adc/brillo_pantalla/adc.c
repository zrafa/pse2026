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
        uint8_t adcl;               /* ADC Data Register Low */
	/* COMPLETAR */

        uint8_t adch; /* ADC Data Register High */
        uint8_t adc_status_control_a; /* ADC Status and Control A */
        uint8_t adc_status_control_b; /* ADC Status and Control B */
        uint8_t adc_mux; /* ADC Multiplexor */
        uint8_t adc_reserved_data; /* ADC Reserved Data */
        uint8_t adc_didr0; /* ADC DIDR0 */

} volatile adc_t;

volatile adc_t *adc = (adc_t *) (0x78); /* direccion del primer registro */


void adc_init() {
        /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
        de vcc con capacitor externo y encender (habilitar) el periferico */

        //Habilito el ADC con el bit 7 del registro de control y estado A
        adc->adc_status_control_a |= (1 << 7);

        //Poniendo en 1 el bit 6 y dejando en 0 el bit 7 del multiplexor se utiliza el voltaje de vcc con capacitor externo
        adc->adc_mux |= (1 << 6);

        /* Establecer tambien el prescalar para lograr un valor acorde (divisor) */
        //frecuencia de adc entre 50 y 200 kHz, frecuencia de CPU: 16 mHz y f_adc = f_cpu/divisor (prescalar)
        adc->adc_status_control_a |= (1 << 2) | (1 << 1) | (1 << 0);
}

int adc_get(char input)
{
        /* 1. Selects which analog input is connected to the ADC */
        //Ponemos como canal de entrada ADC2
        adc->adc_mux |= (1 << 1);

        /* 2. Write this bit to one to start each conversion */
        adc->adc_status_control_a |= (1 << 6);

        /* 3. When conversion is complete, it returns to zero */

        /* 4. When conversion is complete, read the data register */
        /* IMPORTANT: ADCL must be read first, then ADCH */
        int value = adc->adcl;
        value |= (adc->adch << 8);

	/* return the value */
        return value;
}
