#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "timer2.h"


int main()
{
	float val;

	serial_init();
	timer2_init();

	//Habilitamos las interrupciones a nivel global
	sei();

	while (1) {
		int ticks = timer2_getticks();
		serial_put_int(ticks, 3);
		serial_put_char(' ');
		serial_put_char('\r');
	}

	for(;;);
}
