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

volatile timer2 *timer = (timer2 *) (0xb0);

char *timsk2 = (char * ) 0x70; //Mascara del timer

#define WGM20 0
#define WGM21 1
#define WGM22 3
#define CS20 0
#define CS21 1
#define CS22 2
#define OCEI2A 1
#define COM2A1 7
#define COM2A0 6

char tope_actual = 0;

void init_timer(){
    //modo PWM

    timer->tccr2a |= (1<< WGM20); //Lo pongo en 1
    timer->tccr2a |= (1<< WGM21); // Lo pongo en 1
    timer->tccr2b &= ~(1<< WGM22);
    timer->tccr2b |= (1<< CS20) | (1<< CS21) | (1<< CS22); //Preescalar

    timer->tccr2a &= ~(1<< COM2A0); // Lo pongo en 0
    timer->tccr2a |= (1<< COM2A1); // Lo pongo en 1

    //256 * 10 / 16,384 = 156,25 
    //Lo ssteamos en 155 OCR
    //preescalar seria cs20 21 y 22 para 1024
    
    timer -> ocr2a = 255;

    //Habilitar interrumpciones especificas del timer

    *timsk2 |= (1<<OCEI2A); 
    /*the Timer/Counter2 compare match A interrupt is enabled*/
}

void actualizar_tope(char tope){
        timer -> ocr2a = tope;

}