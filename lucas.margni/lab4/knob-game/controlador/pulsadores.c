#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#define PIN_PULSADOR 0

/* tiempo de espera por oscilaciones del pulsador */
#define ESPERA 10000

/* puertos de E/S */
volatile unsigned char *puerto_b = (unsigned char *) 0x25;  /* PORTB (datos) */
volatile unsigned char *ddr_b = (unsigned char *) 0x24;     /* DDRB (control) */
volatile unsigned char *pin_b = (unsigned char *) 0x23;     /* PINB (entrada) */

/* configuracion inicial pulsadores */
void pulsadores_init() {
	// configurar pulsador - ENTRADA
	*ddr_b &= ~(1 << PIN_PULSADOR);

	// activamos el pull-up del pulsador
	*puerto_b |= (1 << PIN_PULSADOR);
}

/* revisar si algun pulsador fue presionado */
char verificar_pulsacion() {
    char pulsador_presionado = 0;

    // se revisa si el pulsador fue pulsado
    if(!((*pin_b >> PIN_PULSADOR) & 1)) {
        // se presiono el pin left
        pulsador_presionado = 1;
    }

    _delay_us(ESPERA);

    return pulsador_presionado;
}