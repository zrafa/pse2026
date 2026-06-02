#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Timer 2 modificado para controlar el servomotor (usando timer 1?)

/*typedef struct{
    uint8_t tccr2a;
    uint8_t tccr2b;
    uint8_t tcnt2;
    uint8_t ocr2a;
    uint8_t ocr2b;
} volatile timer2; */

typedef struct
{
    uint8_t tccr1a; // 0x80
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
    uint8_t ocr1bh; // 0x8B
} volatile timer1_t;

// volatile timer2 *timer = (timer2 *)(0xb0);
volatile timer1_t *timer1 = (timer1_t *)0x80;

// char *timsk2 = (char *)0x70; // Mascara del timer
volatile uint8_t *timsk1 = (uint8_t *)0x6f;

//(TCCR1A)
#define WGM10 0
#define WGM11 1
#define COM1A0 6
#define COM1A1 7

//(TCCR1B)
#define CS10 0
#define CS11 1
#define WGM12 3
#define WGM13 4

long long centesimas = 0;
void init_timer()
{
    /*   timer->tccr2a &= ~(1 << WGM20); // Lo pongo en 0
       timer->tccr2a |= (1 << WGM21);  // Lo pongo en 1
       timer->tccr2b &= ~(1 << WGM22);
       timer->tccr2b |= (1 << CS20) | (1 << CS21) | (1 << CS22);
       
    // 256 * 10 / 16,384 = 156,25
    // Lo ssteamos en 155 OCR
    // preescalar seria cs20 21 y 22 para 1024
    // timer->ocr2a = 155;
    // Habilitar interrumpciones especificas del timer
    //*timsk2 |= (1 << OCEI2A);
*/

    // Configurar el pin OC1A (PB1) como salida (0x24 es DDRB)
    *(volatile uint8_t*)0x24 |= (1 << 1);

    /* modo Fast PWM (14) */

    //Limpio los registros
    timer1->tccr1a = 0;
    timer1->tccr1b = 0;

    //Clear on match
    timer1->tccr1a |= (1 << COM1A1);

    // Modo 14: Fast PWM con tope en ICR1 (WGM13=1, WGM12=1, WGM11=1, WGM10=0)
    timer1->tccr1a |= (1 << WGM11);
    timer1->tccr1b |= (1 << WGM13) | (1 << WGM12);

    //Configurar el tope (TOP) para 50Hz.
    // 1450 0x05aa
    timer1->icr1h = 0x05; 
    timer1->icr1l = 0xAA;

    // Configurar el ciclo de trabajo inicial en 1ms (250 ticks).
    // 250 en decimal es 0x00FA en hexadecimal.

    timer1->ocr1ah = 0x00;
    timer1->ocr1al = 0xFA;

    // Arrancar el timer con preescalar de 1 
    timer1->tccr1b |=(1 << CS10);
  
}

long long get_timer()
{
    return centesimas;
}

void actualizar_servo(uint16_t ticks){

    uint8_t byte_alto = (uint8_t)(ticks >> 8);
    uint8_t byte_bajo = (uint8_t)(ticks & 0xFF);

    timer1->ocr1ah = byte_alto;
    timer1->ocr1al = byte_bajo;
}