/**********************************************************************
 *
 * adc.c - Driver del ADC del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>
#include "adc.h"

/* Estructura de datos del driver ADC */

typedef struct {
    uint8_t adcl;       /* ADC Data Register Low */
    uint8_t adch;       /* ADC Data Register High */
    uint8_t adcsr_a;    /* ADC Control and Status Register A */
    uint8_t adcsr_b;    /* ADC Control and Status Register B */
    uint8_t admux;      /* ADC Multiplexer Selection Register */
    uint8_t reserved;
    uint8_t didr0;      /* Digital Input Disable Register 0 */

} volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78;

/* Inicializar driver ADC */
void adc_init() {
    /* Configurar ADMUX para utilizar voltaje de vcc con capacitor externo, bit REFS0 (7) en 1 y REFS1 (6) en 0 */
    adc->admux |= 1 << 6;
    adc->admux &= ~(1 << 7);

    /* Habilitar el periferico, prendiendo el bit ADEN (7) del ADCR_A */
    adc->adcsr_a |= 1 << 7;

    /* Establecer tambien el prescalar para lograr un valor acorde (divisor)
    f_adc entre 50 y 200 kHz, f_cpu = 16 mHz, f_adc = f_cpu / prescalar
    Valor acorde para prescalar: 128, bits ADP2:0 (2:0) del ADCR_A todos en 1 */
    adc->adcsr_a |= 1 << 2 | 1 << 1 | 1 << 0;
}

/* Obtener datos de entrada por ADC en el pin correspondiente a input */
int adc_get(char input) {
    /* 1. Seleccionar cual entrada analoga esta conectada al ADC, bits MUX3:0 (3:0) del ADMUX */
    if (input >= 0 && input <= 8) {
        // input valido
        adc->admux |= input;
    }
    // si no es valido se deja por defecto al 0

    /* 2. Escribir el bit ADSC (6) del ADCSR_A en uno para empezar cada conversion */
    adc->adcsr_a |= 1 << 6;

    /* 3. Esperar a que la conversion se complete (ADSC se ponga en 0) */
    while((adc->adcsr_a >> 6) & 1);

    /* 4. Leer el registro de datos. ADCL se debe leer antes que ADCH */
    int resultado = adc->adcl;
    resultado |= adc->adch << 8;

    return resultado;
}
