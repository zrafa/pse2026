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
	uint8_t adch;           /* ADCH — ADC Data Register High */
        uint8_t status_control_a;
        uint8_t status_control_b;
        uint8_t admux; 
        uint8_t reservado;
        uint8_t didr0;
} volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78; // direccion del primer registro */


/* ADMUX */
#define REFS1   7
#define REFS0   6   /* Referencia AVCC con capacitor externo             */
#define ADLAR   5   /* Left-adjust: resultado de 8 bits en ADCH          */
#define MUX3    3   /* Canal analógico bit 3                             */
#define MUX2    2   /* Canal analógico bit 2                             */
#define MUX1    1   /* Canal analógico bit 1                             */
#define MUX0    0   /* Canal analógico bit 0                             */
 
/* ADCSRA */
#define ADEN    7   /* Habilitar ADC                                     */
#define ADSC    6   /* Iniciar conversión                                */
#define ADPS2   2   /* Prescaler bit 2  \                                */
#define ADPS1   1   /* Prescaler bit 1   > 111 = /128 → 125kHz          */
#define ADPS0   0   /* Prescaler bit 0  /                                */

void adc_init()
{
        /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
        de vcc con capacitor externo y encender (habilitar) el periferico */
        adc->status_control_a |= (1<<ADEN); //|(1<<ADSC);
        adc->admux |= (1<<REFS0);
        adc->admux &= ~(1<<REFS1);

        /* Establecer tambien el prescalar para lograr un valor acorde (divisor) */
        adc->status_control_a |=  (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

        adc -> admux &= ~ (1 << ADLAR); //AGREGUE ESTO
}

int adc_get(char input)
{
	
        if(input>8 || input<0){
                return -1;
        }

        /* 1. Selects which analog input is connected to the ADC */

                adc->admux |= input;
                adc->admux &= (input | 0b11110000);
        /* 2. Write this bit to one to start each conversion */

                adc->status_control_a |= (1<<ADSC);
        
        /* 3. When conversion is complete, it returns to zero */

                while(adc->status_control_a & ((1<<ADSC)));

        /* 4. When conversion is complete, read the data register */
        /* IMPORTANT: ADCL must be read first, then ADCH */

                uint16_t data = adc->adcl; //int 
                data += ((adc->adch) & (0b00000011)) * 256;

        return data;
}

void delay_ms(int ms){
        volatile i;
        volatile j;

        for(i=0;i<ms;i++){
                for(j=0; j<452;j++);
        }
}