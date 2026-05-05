#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL

#include <util/delay.h>
#include "speaker.h"

#define PIN_SOUND 0

/* puertos de E/S */

volatile unsigned char *puerto_b = (unsigned char *) 0x25;  /* PORTB (datos) */
volatile unsigned char *ddr_b = (unsigned char *) 0x24;     /* DDRB (control) */
volatile unsigned char *pin_b = (unsigned char *) 0x23;     /* PINB (entrada) */

/* Configura el puerto de salida */
void speaker_init() {
	*ddr_b |= 1 << PIN_SOUND;
}

/* Reproduce una nota en una frecuencia durante cierta duracion */
void reproducir_nota(int frecuencia, int duracion_ms) {
    if (frecuencia == 0) {
        silencio(duracion_ms);
        return;
    }

    // Tiempo que se mantiene en alto y en bajo
    int medio_periodo_us = (1000000UL / frecuencia) / 2;
    
    // Cantidad de ciclos necesarios para alcanzar la duracion adecuada
    int ciclos = ((int)frecuencia * duracion_ms) / 1000;

    for (int i = 0; i < ciclos; i++) {
        // poner señal en alto
        *puerto_b |= (1 << PIN_SOUND);

        // esperar
        _delay_us(medio_periodo_us);
        
        // poner señal en bajo
        *puerto_b &= ~(1 << PIN_SOUND);

        // esperar
        _delay_us(medio_periodo_us);
    }
}

/* Hace un silencio durante una duracion */
void silencio(int duracion_ms) {
    _delay_us(duracion_ms * 1000);
}