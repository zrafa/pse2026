#include <stdint.h>
#include "timer2.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t ticks_centesimas = 0;
ISR(TIMER2_COMPA_vect) {
    ticks_centesimas++;
}

typedef struct
{
  uint8_t controlA; // TCCR2A en 0xB0
    uint8_t controlB; // TCCR2B en 0xB1
    uint8_t counter;  // TCNT2  en 0xB
    uint8_t compareA; // OCR2A  en 0xB3
    uint8_t compareB; // OCR2B  en 0xB4 
} volatile timer8;



volatile timer8 *timer2 = (timer8 *)(0x80);

void timer2_init_ctc(void) {//config inicial
    timer2->controlB = 0b00000111;  //bits CS22, CS21 y CS20 en 1
    timer2->controlA = 0b00000010; //Modo CTC WGM12

    //se reinicia el contador
    timer2->counter = 0;

    // seteo el tope para 1 centésima de segundo a 16MHz
    timer2->compareA = 155;
    
    //interrupcion del timer 2
TIMSK2 = 0b00000010; // Pone en 1 el bit 1
    //interrupciones globales
 SREG |= 0b10000000;  // Pone en 1 el bit 7
   
}
