#include "timer.h"
#include "serial.h"
#include <math.h>
#include <stdint.h>

void main(){

    init_timer();
    serial_init();

    unsigned char dato;
    uint16_t auxiliar;

    while(1)
    {
	dato = serial_get_char();

	// Lo tenemos en un rango de 0 a 255 y lo queremos pasar a 0 a 290

	auxiliar = ((uint16_t) dato) * 290 / 255;

	cambiar_tope(auxiliar);

    }
}
