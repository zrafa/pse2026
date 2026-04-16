/*
 * ultrasound: programa que controla el HC-SR04 para medir distancias en cm
 */

#include "serial.h"
#include "ultrasound.h"

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>

int main(void)
{
	serial_init();
	ultrasound_init();
	   
	/* un programa embebido nunca finaliza */
	for (;;) {
        int dist_cm = ultrasound_get_distance();
        
        serial_put_str("Distancia: ");
        if (dist_cm == -1) {
            serial_put_str("---"); 
        } else {
            serial_put_int(dist_cm, 4);
        }
        serial_put_str(" cm\r\n");

        _delay_ms(500); // Esperar medio segundo entre lecturas
    }
}

