#include <util/delay.h>
#include "utils.h"

// pin d8 puerto b
#define PARLANTE_PIN 0

volatile unsigned char * ddr_b    = (unsigned char *) 0x24;
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

void parlante_init(void) {
    // |= prende un bit especifico en este caso PARLANTE_PIN
    *ddr_b |= (1 << PARLANTE_PIN);
}

void tocar_nota(int frecuencia, int duracion_ms) {
    if (frecuencia == 0) {
        silencio(duracion_ms);
        return;
    }

    // Calculamos el tiempo que el pin debe estar en ALTO y en BAJO (semi-periodo)
    int semi_periodo_us = (1000000UL / frecuencia) / 2;
    
    // Calculamos cuántos ciclos completos necesitamos para alcanzar la duración
    int ciclos = ((int)frecuencia * duracion_ms) / 1000;

    for (int i = 0; i < ciclos; i++) {
        *puerto_b |= (1 << PARLANTE_PIN);   // Pin en ALTO
        for (int j = 0; j < semi_periodo_us; j++) {
            _delay_us(1);
        }
        *puerto_b &= ~(1 << PARLANTE_PIN);  // Pin en BAJO
        for (int j = 0; j < semi_periodo_us; j++) {
            _delay_us(1);
        }
    }
}

void silencio(int duracion_ms) {
    for (int i = 0; i < duracion_ms; i++) {
        _delay_ms(1);
    }
}