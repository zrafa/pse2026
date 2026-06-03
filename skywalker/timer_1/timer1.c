/*
Timer init (dos modos: normal o pwm, y que cosas va a contar).
Agregar una función para configurar el pwm (usar un modo en donde el
tope es configurable).
Que se pueda habilitar uno de los dos canales, y usarlos con PWM.
Agregar una función para poder obtener el valor del timer.

Probar un servo y el reproductor de sonido con ese driver.
*/
#include "timer1.h"
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

volatile timer1_t *timer1 = (timer1_t *)0x80;

volatile uint8_t *timsk1 = (uint8_t *)0x6f;

void init_timer(uint8_t mode, uint8_t prescalar)
{
    // Mode 1 = Normal
    // Mode 2 = PWM
    *(volatile uint8_t *)0x24 |= (1 << 1);

    timer1->tccr1a = 0;
    timer1->tccr1b = 0;

    switch (mode)
    {
    case NORMAL:
        // Necesita 4 pines en 0
        break;
    case PWM:
        timer1->tccr1a |= (1 << WGM11);
        timer1->tccr1b |= (1 << WGM13) | (1 << WGM12);

        // Configurar el tope
        timer1->icr1h = 0xFF;
        timer1->icr1l = 0xFF;

        // Ciclo de trabajo
        break;
    default:
        printf("Error :D");
        break;
    }

    // Ajusta el preescalar o si es fuente externa
    timer1->tccr1b = prescalar;
}

uint16_t get_timer()
{
	return (((uint16_t) timer1->tcnt1h) << 8) | timer1->tcntl1l;
}

void configure_comparator(uint16_t top, uint8_t mode)
{
    // top de la amplitud del ciclo?
    uint8_t byte_high = (uint8_t)(top >> 8);
    uint8_t byte_low = (uint8_t)(top & 0xFF);

	if(mode == A){
    		timer1->ocr1ah = byte_high;
    		timer1->ocr1al = byte_low;
	} else if(mode == B){
    		timer1->ocr1bh = byte_high;
    		timer1->ocr1bl = byte_low;
	}
}

void configure_top(uint16_t top)
{
    // Ciclo de trabajo
    uint8_t byte_high = (uint8_t)(top >> 8);
    uint8_t byte_low = (uint8_t)(top & 0xFF);

    timer1->icr1h = byte_high;
    timer1->icr1l = byte_low;
}
