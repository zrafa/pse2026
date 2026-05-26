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

/* Estructura de datos del driver para timer2 */

//Guardamos los ticks en una variable global
volatile int ticks = 0;
volatile int ticks_simulados = 0;

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
        /* El timer viene configurado por defecto en modo normal, lo ponemos en CTC */
        //Lo ponemos en modo CTC poniendo el bit WGM21 en 1
        timer2->control_a |= (1 << 1);

        //Ahora definimos 64 como prescalar poniendo en 1 el bit CS22 del registro de control B
        timer2->control_b |= (1 << 2);

        //Ahora ponemos el valor que queremos setear como tope en el OCRA
        timer2->output_compare_a = 250;

        //Ahora habilitamos las interrupciones cuando el contador alcance el valor almacenado en OCRA
        (*interrupt_mask) |= 0x02;
}

int timer2_getticks() {
        return ticks;
}

//Rutina de atención de interrupciones
ISR(TIMER2_COMPA_vect){
        ticks_simulados++;
        if(ticks_simulados == 10){
                //Cada 10 ticks simulamos un tick
                ticks++;
                ticks_simulados = 0;
        }
}