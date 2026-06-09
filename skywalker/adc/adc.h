/**********************************************************************
 *
 * Filename:    adc.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

/* ADMUX */
#define REFS1 7
#define REFS0 6 /* Referencia AVCC con capacitor externo             */
#define ADLAR 5 /* Left-adjust: resultado de 8 bits en ADCH          */
#define MUX3 3  /* Canal analógico bit 3                             */
#define MUX2 2  /* Canal analógico bit 2                             */
#define MUX1 1  /* Canal analógico bit 1                             */
#define MUX0 0  /* Canal analógico bit 0                             */

/* ADCSRA */
#define ADEN 7  /* Habilitar ADC                                     */
#define ADSC 6  /* Iniciar conversión                                */
#define ADPS2 2 /* Prescaler bit 2  \                                */
#define ADPS1 1 /* Prescaler bit 1   > 111 = /128 → 125kHz          */
#define ADPS0 0 /* Prescaler bit 0  /                                */

#ifndef _ADC_H
#define _ADC_H

void adc_init(void);
int adc_get(char);
void delay_ms();

#endif 