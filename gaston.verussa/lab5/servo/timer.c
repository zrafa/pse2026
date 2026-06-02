#include <stdint.h> 
#include <avr/io.h>
#include <avr/interrupt.h>


typedef struct{
    uint8_t tccr1a;
    uint8_t tccr1b;
    uint8_t tccr1c;
    uint8_t reserved;
    uint8_t tcnt1l;
    uint8_t tcnt1h;
    uint8_t icr1l;
    uint8_t icr1h;
    uint8_t ocr1al;
    uint8_t ocr1ah;
    uint8_t ocr1bl;
    uint8_t ocr1bh;
} volatile timer1;

timer1 *timer = (timer1 *) (0x80);

char *ddrb = (char * ) 0x24;

//	 El tope es 40.000 para los 20ms, entonces los topes varian de 1 a 2 ms
uint16_t min_tope = 2000;
uint16_t max_tope = 4000;
uint16_t tope_actual = 2000;
char subiendo = 1;

#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4
#define CS10 0
#define CS11 1
#define CS12 2
#define OCIE2A 1
#define COM2A1 7
#define COM2A0 6
#define DDB1 1

int init_timer(){

    // Setea el comportamiento en fast PWM con tope 0xFF
    timer->tccr1a &= ~(1<< WGM10); //Lo pongo en 1
    timer->tccr1a |= (1<< WGM11); // Lo pongo en 1
    timer->tccr1b |= (1<< WGM12) | (1 << WGM13); //	 Lo pongo en 0

    // Setea el prescalar en 8
    timer->tccr1b &= ~(1<< CS10);
    timer->tccr1b |= (1<< CS11);
    timer->tccr1b &= ~(1<< CS12);

    // Setea el comportamiento de OC1A

    timer -> tccr1a |= (1 << COM1A1);
    timer -> tccr1a &= ~(1 << COM1A0);

    // Setea el tope para una frecuencia de 11025hz, en 39999 = 0x9C3F

    timer -> icr1h = 0x9C;
    timer -> icr1l = 0x3F;

    // Setea el pin PB1 como salida, para tener la salida PWM
    *ddrb |= (1 << DDB1);

}

void cambiar_tope(uint16_t tope)
{
	// Recibe el tope de 0 a 1023, debe transformarlo del menor tope a mayor tope
/*
	if(subiendo == 1)
	{
	   tope_actual++;
	   if(tope_actual == 4000)
		subiendo = 0;
	}
	else
	{
	   tope_actual--;
	   if(tope_actual == 2000)
	       subiendo = 1;
	}
*/
    uint16_t auxiliar = tope * 2 + 499;

    if(auxiliar > 2499)
        auxiliar = 2499;

    uint8_t byte_alto = (uint8_t) (auxiliar >> 8);
    uint8_t byte_bajo = (uint8_t) (auxiliar & 0xFF);

    timer -> ocr1ah = byte_alto;
    timer -> ocr1al = byte_bajo;
}
