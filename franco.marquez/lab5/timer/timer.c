#include <stdint.h> 

typedef struct{
    uint8_t TCCR2A;
    uint8_t TCCR2B;
    uint8_t TCNT2;
    uint8_t OCR2A;
    uint8_t OCR2B;
} timer2;

timer2 *timer = (timer2 *) (0xb0);

char *timsk2 = (char * ) 0x70;

#define WGM20 0
#define WGM21 1
#define WGM22 3
#define CS20 0
#define CS21 1
#define CS22 2


int init_timer(){

    timer->TCCR2A &= ~(1<< WGM20) //Lo pongo en 0 
    timer->TCCR2A |= (1<< WGM21) // Lo pongo en 1
    timer->TCCR2B &= ~(1<< WGM22)
    timer->TCCR2B |= (1<< CS20) | (1<< CS21) | (1<< CS22);

    //256 * 10 / 16,384 = 156,25 
    //Lo ssteamos en 155 OCR
    //preescalar seria cs20 21 y 22 para 1024

    timer -> OCR2A = 155;

    //Habilitar interrumpciones especificas del timer

    //las interup globales se hacen desde el main
}

