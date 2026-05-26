/**********************************************************************
 *
 * timer2.c - Driver del timer2 del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include <avr/interrupt.h>
#include <avr/io.h>

/* Generar 100 interrupciones por segundo, en este caso los prescalares no nos dan números redondos, por lo que hacemos 1000 interrupciones por segundo y simulamos 100 

Utilizamos el modo CTC. TOP es definido por OCR2A. Cuando CONTADOR == TOP, TOP se pone en 0.

Reloj del sistema: 16000000 de ticks / 64 (prescalar) = 250000 ticks

250000 ticks/s / 1000 ticks/s = 250

Esto significa que tengo que poner el valor 250 como TOP para que se realicen 1000 interrupciones por segundo con el prescalar 64.
*/

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

//Puerto D

/* direccion de PORTD (registro de datos) */
volatile unsigned char * puerto_d = (unsigned char *) 0x2B;

/* direccion de DDR D (registro de control) */
volatile unsigned char * ddr_d = (unsigned char *) 0x2A;

/* direccion PIN D (registro de datos de entrada) */
volatile unsigned char * pin_d = (unsigned char *) 0x29;


/* Estructura de datos del driver para timer2 */

typedef struct
{
        uint8_t control_a;    /* timer2 Control register A */
        uint8_t control_b;    /* timer2 Control register B */
        uint8_t timer_register;    /* tcnt2 timer2 Register */
        uint8_t output_compare_a;    /* timer2 Output Compare register A */
        uint8_t output_compare_b;    /* timer2 Output Compare register B */
} volatile timer2_t;

volatile timer2_t *timer2 = (timer2_t *) (0xB0); /* direccion del primer registro */

/* Registro mascara de interrupciones de timer 2 */
volatile unsigned char *interrupt_mask = (unsigned char *)(0x70);


void timer2_init() {
        /* El timer viene configurado por defecto en modo normal, lo ponemos en Fast PWM */
        //Lo ponemos en modo CTC poniendo el bit WGM20, WGM21, WGM22 en 1
        timer2->control_a |= (1 << 1 || 1 << 0);

        //Tengo que cambiar el valor de OCR2B recibiendo lo que entre por ADC para cambiar la señal en alto o bajo

        //Ahora definimos 64 como prescalar poniendo en 1 el bit CS22 del registro de control B
        timer2->control_b |= (1 << 2);


        //Quiero que compare con el registro OC2A y lo ponga en bajo cuando se alcance (non-inverting mode)
        timer2->control_a |= (1 << 7);
        //Hacemos lo mismo para OC2B
        timer2->control_a |= (1 << 5);

        //Ponemos los puertos PB3 y PD3 como salida para las señales
        //Configura el puerto B bit 3 como salida
	*ddr_b |= 1 << 3;

	//Configura el puerto D bit 3 como salida
	*ddr_d |= 1 << 3;
}

void timer2_setvalor(int valor){
        timer2->output_compare_a = valor;
        timer2->output_compare_b = valor;
}
