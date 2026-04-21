#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serial.h"

/* pines a conectar para el funcionamiento del juego */
#define PIN_LEFT 0
#define PIN_RIGHT 1
#define PIN_ROTATE 2
#define PIN_DROP 3

#define PIN_QUIT 0
#define PIN_PAUSE 1
#define PIN_BOSS 2
#define PIN_SAVE 3

/* teclas asociadas a cada pin */
#define LEFT 'a'
#define RIGHT 'd'
#define ROTATE 'w'
#define DROP 's'

#define QUIT 'q'
#define PAUSE 'p'
#define BOSS 'b'
#define SAVE 'e'

/* tiempo de espera por oscilaciones del pulsador */
#define ESPERA 100000

/* puertos de E/S */
volatile unsigned char *puerto_b = (unsigned char *) 0x25; // PORTB (datos)
volatile unsigned char *ddr_b = (unsigned char *) 0x24; // DDRB (control)
volatile unsigned char *pin_b = (unsigned char *) 0x23; // PINB (entrada)

volatile unsigned char *puerto_c = (unsigned char *) 0x28; // PORTC (datos)
volatile unsigned char *ddr_c = (unsigned char *) 0x27; // DDRC (control)
volatile unsigned char *pin_c = (unsigned char *) 0x26; // PINC (entrada)

/* configuracion inicial pulsadores */
void pulsadores_init() {
	// configurar pulsadores - ENTRADA
	*ddr_b &= ~((1 << PIN_LEFT) | (1 << PIN_RIGHT) | (1 << PIN_ROTATE) | (1 << PIN_DROP));
    *ddr_c &= ~((1 << PIN_QUIT) | (1 << PIN_PAUSE) | (1 << PIN_BOSS) | (1 << PIN_SAVE));

	// activamos el pull-up a cada pulsador
	*puerto_b |= (1 << PIN_LEFT) | (1 << PIN_RIGHT) | (1 << PIN_ROTATE) | (1 << PIN_DROP);
    *puerto_c |= (1 << PIN_QUIT) | (1 << PIN_PAUSE) | (1 << PIN_BOSS) | (1 << PIN_SAVE);

    // inicializar el driver serial
    serial_init();
}

/* revisar si algun pulsador fue presionado */
void verificar_pulsacion() {
    char i = 0;
    char pulsador_encontrado = 0;

    // se revisan los pines en orden, el primero que se enecuentra es el que se toma como presionado
    if(!((*pin_b >> PIN_LEFT) & 1)) {
        // se presiono el pin left
        serial_put_char(LEFT);

    } else if(!((*pin_b >> PIN_RIGHT) & 1)) {
        // se presiono el pin right
        serial_put_char(RIGHT);

    } else if(!((*pin_b >> PIN_ROTATE) & 1)) {
        // se presiono el pin rotate
        serial_put_char(ROTATE);
        
    } else if(!((*pin_b >> PIN_DROP) & 1)) {
        // se presiono el pin drop
        serial_put_char(DROP);

    } else if(!((*pin_c >> PIN_QUIT) & 1)) {
        // se presiono el pin quit
        serial_put_char(QUIT);
        
    } else if(!((*pin_c >> PIN_PAUSE) & 1)) {
        // se presiono el pin pause
        serial_put_char(PAUSE);
        
    } else if(!((*pin_c >> PIN_BOSS) & 1)) {
        // se presiono el pin boss
        serial_put_char(BOSS);
        
    } else if(!((*pin_c >> PIN_SAVE) & 1)) {
        // se presiono el pin save
        serial_put_char(SAVE);
        
    }
    // espera por posibles oscilaciones
    _delay_us(ESPERA);
}