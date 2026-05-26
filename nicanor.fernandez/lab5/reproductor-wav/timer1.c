/**********************************************************************
 *
 * timer1.c - Driver del timer1 del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */
#include <avr/interrupt.h>
#include <avr/io.h>

/* Debemos buscar generar interrupciones con una frecuencia aproximada de 11025hz
1 / 11025 me da la cantidad de interrupciones por SEGUNDO que quiero = 0.0000907 interrupciones por segundo
Esto es igual a 90.7 interrupciones por microsegundo

Reloj del sistema: 16000000 de ticks por segundo = 16 ticks por microsegundo
16 ticks por microsegundo / 1 (prescalar) = 16 ticks por microsegundo
16 ticks por microsegundo * 90.7 interrupciones por microsegundo = 1451 ticks por interrupcion



Esto significa que tengo que poner el valor 1451 como TOP para que se realicen 90.7 interrupciones por microsegundo con el prescalar 1.
*/

//Definimos los ticks
volatile int ticks = 0;


// direccion de DDR B (registro de control) 
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* Estructura de datos del driver para timer1 */

typedef struct
{
        uint8_t control_a;    /* timer1 Control register A */
        uint8_t control_b;    /* timer1 Control register B */
        uint8_t control_c;    /* timer1 Control register C */
        uint8_t reserved;    /* timer1 reserved bits */
        uint8_t tcnt_low;    /* tcnt1 Timer 1 Control Register Low byte */
        uint8_t tcnt_high;    /* tcnt1 Timer 1 Control Register High byte */
        uint8_t input_capture_low;    /* timer1 Input Capture register Low byte */
        uint8_t input_capture_high;    /* timer1 Input Capture register High byte */
        uint8_t output_compare_a_low;    /* timer1 Output Compare register A Low byte */
        uint8_t output_compare_a_high;    /* timer1 Output Compare register A High byte */
        uint8_t output_compare_b_low;    /* timer1 Output Compare register B Low byte */
        uint8_t output_compare_b_high;    /* timer1 Output Compare register B High byte */
} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *) (0x80); /* direccion del primer registro */

/* Registro mascara de interrupciones de timer 1 */
volatile unsigned char *interrupt_mask = (unsigned char *)(0x6F);


void timer1_init() {
        /* El timer viene configurado por defecto en modo normal, lo ponemos en Fast PWM Modo 14*/
        //Se ponen los bits WGM0 en 0 y WGM1, WGM2 y WGM3 en 1
        timer1->control_a |= (1 << 1);
        timer1->control_b |= (1 << 3 || 1 << 4);

        //Quiero que compare con el registro OCR1A, por lo que pongo el bit COM1A1 en 1 y el COM1A0 en 0
        timer1->control_a |= (1 << 7);

        //Definimos un preescalar de 1, por lo que ponemos los bits CS10 en 0, CS11 en 1 y CS12 en 1
        timer1->control_b |= (1 << 0);

        //Configura el puerto B bit 3 como salida
	*ddr_b |= 1 << 3;

        //Guardamos el TOP en el registro ICR1, que es el registro que define el TOP en el modo Fast PWM, tiene que ser 1451 (en hexadecimal son 0x05ab) por la cuenta que hicimos antes
        timer1->input_capture_low = 0xab;
        timer1->input_capture_high = 0x05;

        //Habilitamos la interrupcion de comparacion A, que es la que se va a generar cada vez que el timer llegue al valor del registro OCR1A
        *interrupt_mask |= (1 << 1);
}

ISR(TIMER1_COMPA_vect) {
        ticks++;
}

void timer1_setvalor(uint16_t valor){
        timer1->output_compare_a_high = (valor >> 8) & 0x00FF; // Obtenemos el byte alto
        timer1->output_compare_a_low = valor & 0x00FF; // Obtenemos el byte bajo
}
