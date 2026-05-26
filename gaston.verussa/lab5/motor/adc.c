/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */

/* Estructura de datos del driver ADC */

typedef struct
{
        uint8_t adcl;               /* ADC Data Register Low */
	uint8_t adch;
	uint8_t adcsra;
	uint8_t adcsrb;
	uint8_t admux;
	uint8_t reserved;
	uint8_t didr0;
	uint8_t didr1;
	/* COMPLETAR */

} volatile adc_t;

volatile adc_t *adc = (adc_t *) 0x78; /* direccion del primer registro */

#define REFS0 6
#define REFS1 7
#define ADEN 7
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADSC 6
#define ADLAR 5

void adc_init()
{
        /* Configurar los registros ADMUX y ADCSRA para utilizar el voltaje
        de vcc con capacitor externo y encender (habilitar) el periferico */

	adc -> admux |= (1 << REFS0);
	adc -> admux &= ~(1 << REFS1);

	adc -> adcsra |= (1 << ADEN);
        /* Establecer tambien el prescalar para lograr un valor acorde (divisor) */

	adc -> adcsra |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);

	//	Define la lectura por izquierda o derecha
	adc -> admux &= ~(1 << ADLAR);
}

int adc_get(char input)
{

	//  Checkea que este entre 0 y 8
	if(input < 0 || input > 8){
		return 48;
	}
        /* 1. Selects which analog input is connected to the ADC */

	adc->admux |= input;
	//	Se le ponen los primeros 4 bits a input en 1 para no afectar
	//		dichos bits del admux
	adc->admux &= (input | 0b11110000);

        /* 2. Write this bit to one to start each conversion */
	adc->adcsra |= (1 << ADSC);

        /* 3. When conversion is complete, it returns to zero */

	while(adc->adcsra & (1 << ADSC));

        /* 4. When conversion is complete, read the data register */
        /* IMPORTANT: ADCL must be read first, then ADCH */

	int valor_a_devolver = adc -> adcl;

	//
	valor_a_devolver += ((adc -> adch) & (0b00000011)) * 256;

	return valor_a_devolver;
	/* return the value */
}
