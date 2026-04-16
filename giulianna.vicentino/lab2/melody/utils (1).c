#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz para el Arduino Nano
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"

// El pin 8 de Arduino corresponde al bit 0 del Puerto B (PB0)
#define PARLANTE_PIN PB0

void parlante_init(void) {
    // Configuramos PB0 como SALIDA
    DDRB |= (1 << PARLANTE_PIN);
}

void tocar_nota(uint16_t frecuencia, uint16_t duracion_ms) {
    if (frecuencia == 0) {
        silencio(duracion_ms);
        return;
    }

    // Calculamos el tiempo que el pin debe estar en ALTO y en BAJO (semi-periodo)
    uint32_t semi_periodo_us = (1000000UL / frecuencia) / 2;
    
    // Calculamos cuántos ciclos completos necesitamos para alcanzar la duración
    uint32_t ciclos = ((uint32_t)frecuencia * duracion_ms) / 1000;

    for (uint32_t i = 0; i < ciclos; i++) {
        PORTB |= (1 << PARLANTE_PIN);   // Pin en ALTO
        for (uint32_t j = 0; j < semi_periodo_us; j++) {
            _delay_us(1);
        }
        PORTB &= ~(1 << PARLANTE_PIN);  // Pin en BAJO
        for (uint32_t j = 0; j < semi_periodo_us; j++) {
            _delay_us(1);
        }
    }
}

void silencio(uint16_t duracion_ms) {
    // Hacemos un bucle de retrasos de 1ms para poder usar variables en la pausa
    for (uint16_t i = 0; i < duracion_ms; i++) {
        _delay_ms(1);
    }
}