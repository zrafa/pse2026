#include <stdint.h> 
#include <avr/io.h>
#include <avr/interrupt.h>


typedef struct{
    uint8_t tccr2a;
    uint8_t tccr2b;
    uint8_t tcnt2;
    uint8_t ocr2a;
    uint8_t ocr2b;
} volatile timer2;

timer2 *timer = (timer2 *) (0xb0);

char *timsk2 = (char * ) 0x70;

char *ddrb = (char * ) 0x24;

#define WGM20 0
#define WGM21 1
#define WGM22 3
#define CS20 0
#define CS21 1
#define CS22 2
#define OCIE2A 1
#define COM2A1 7
#define COM2A0 6
#define DDB3 3

int init_timer(){

    // Setea el comportamiento en fast PWM con tope 0xFF
    timer->tccr2a |= (1<< WGM20); //Lo pongo en 1
    timer->tccr2a |= (1<< WGM21); // Lo pongo en 1
    timer->tccr2b &= ~(1<< WGM22); //	 Lo pongo en 0

    timer->tccr2b |= (1<< CS20) | (1<< CS21) | (1<< CS22); // Setea prescalar mas alto, para mayor velocidad de actualización

    // Setea el comportamiento de OC2A

    timer -> tccr2a |= (1 << COM2A1);
    timer -> tccr2a &= ~(1 << COM2A0);

    timer -> ocr2a = 255;

    // Setea el pin PB3 como salida, para tener la salida PWM
    *ddrb |= (1 << DDB3);

}

void cambiar_tope(char tope)
{
    timer -> ocr2a = tope;
}
