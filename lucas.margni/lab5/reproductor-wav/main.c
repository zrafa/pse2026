#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#include "timer1.h"
#include "serial.h"

void main() {

	timer1_init();
	serial_init();

	unsigned char dato;
	unsigned int valor_mandado;

	timer1_set_comparador(0);

	while (1) {
		dato = serial_get_char();

		/* dato es un valor entre 0 y 255 
		el valor maximo que le paso al timer es 1451/5 = 290 que corresponde a 1V 
		luego el valor final mandado va entre 0 y 290, proporcional al valor de dato 
		255 -> 290
		dato -> ? 
		valor mandado = dato * 290 / 255 */

		valor_mandado = (unsigned int) (dato * 290 / 255);

		timer1_set_comparador(valor_mandado);
	}
}