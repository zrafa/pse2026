#include "ultrasound.h"

volatile unsigned char *ddr_c_ptr    = (unsigned char *) 0x27;
volatile unsigned char *puerto_c_ptr = (unsigned char *) 0x28;
volatile unsigned char *pin_c_ptr    = (unsigned char *) 0x26;

#define TRIG_BIT 2 // pin A2
#define ECHO_BIT 3 // pin A3

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

int ultrasound_get_distance(void)
{
    unsigned int duracion = 0;
    unsigned int timeout = 60000;

    // trigger salida, echo entrada
    *ddr_c_ptr |= (1 << TRIG_BIT);  
    *ddr_c_ptr &= ~(1 << ECHO_BIT); 

    *puerto_c_ptr &= ~(1 << TRIG_BIT); // arranca en 0
    _delay_us(2);
    *puerto_c_ptr |= (1 << TRIG_BIT);  // sube
    _delay_us(10); // 10 us
    *puerto_c_ptr &= ~(1 << TRIG_BIT); // vuelve a 0

    while (!((*pin_c_ptr) & (1 << ECHO_BIT))) {
        // para evitar bloqueos
        if (--timeout == 0) return -1;
    }

    while ((*pin_c_ptr) & (1 << ECHO_BIT)) {
        duracion++;
        _delay_us(1); 
        // para evitar bloqueos
        if (duracion > 30000) return -1; 
    }

    // distancia = (tiempo / 58)
    return (int)(duracion / 58);
}