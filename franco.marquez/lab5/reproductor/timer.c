#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

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
} volatile timer1;

// volatile timer2 *timer = (timer2 *)(0xb0);
volatile timer1 *timer1 = (timer1 *)0x80;

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
    // 4999 en decimal es 0x1387 en hexadecimal.

    timer1->icr1h = 0x13; 
    timer1->icr1l = 0x87;

    // Configurar el ciclo de trabajo inicial en 1ms (250 ticks).
    // 250 en decimal es 0x00FA en hexadecimal.

    timer1->ocr1ah = 0x00;
    timer1->ocr1al = 0xFA;

    // Arrancar el timer con preescalar de 64 (CS11 = 1, CS10 = 1)
    timer1->tccr1b |= (1 << CS11) | (1 << CS10);
  
}

long long get_timer()
{
    return centesimas;
}

void actualizar_servo(uint16_t ticks)
{
    if (ticks < 250) ticks = 250;
    if (ticks > 500) ticks = 500;

    uint8_t byte_alto = (uint8_t)(ticks >> 8);    
    uint8_t byte_bajo = (uint8_t)(ticks & 0xFF);

    timer1->ocr1ah = byte_alto;
    timer1->ocr1al = byte_bajo;
}
// ISR(TIMER2_COMPA_vect)
ISR(TIMER1_COMPA_vect)
{ // Hace esto, cuando la interrupcion se active
    centesimas++;
    if (centesimas == 1000)
    {
    } // Paso un segundo
}