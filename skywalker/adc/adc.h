/**********************************************************************
 *
 * Filename:    adc.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _ADC_H
#define _ADC_H

void adc_init(void);
int adc_get(char);
void delay_ms();

#endif 