/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#include "adc.h"
#include "serial.h"
#include "pulsadores.h"

#include <math.h>

#define ESPERA_US 5000
#define CANT_ESPERAS 10

void main() {
    adc_init();
    serial_init();
    pulsadores_init();

    int cont = 0;
    int valor = 0;
    char pulsado = 0;
    float valor_linealizado = 0.0;

    while(1) {
        valor_linealizado = adc_get(2) / 1024.0;
		valor_linealizado = pow(valor_linealizado, 0.3) * 1024;

        valor = (int) (round(valor_linealizado));
        
        if(cont == CANT_ESPERAS) {
            cont = 0;
            pulsado = verificar_pulsacion();
        } else {
            cont++;
        }

        serial_put_char(valor >> 8);
        serial_put_char(valor & 0xFF);
        serial_put_char(pulsado ? 'S' : 'N');
        
        _delay_us(ESPERA_US);
    }
}

