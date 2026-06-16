/*
 * Aplicación principal para reproducir audio.
 * Inicializa el puerto serie con interrupciones para llenar el buffer,
 * configura el Timer1 en modo PWM rápido y conecta la salida al pin físico.
 * En un bucle infinito, lee muestras del buffer y ajusta el ciclo
 * de trabajo del PWM para generar la onda de sonido.
 */
#include <stdint.h>
#include "../../serial/serial.h"
#include "../../timer_1/timer1.h"

#define TCCR1A (*(volatile uint8_t *)0x80)

int main(void)
{
	char muestra;

	serial_init(115200, 1);
	init_timer(PWM, PRESCALAR_1);
	configure_top(127);
	
	TCCR1A |= (1 << 7);

	while (1) {
		muestra = serial_get_char_buffered();
		configure_comparator((uint8_t)muestra, A);
	}

	return 0;
}