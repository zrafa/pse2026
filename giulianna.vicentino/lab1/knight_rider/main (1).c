
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino
 */

#include "utils.h"

volatile unsigned char estados[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};

int main(void)
{
	led_init();
	int num = 0;
	int dir = 1; // +1 o -1 (modos)
	int max = sizeof(estados) / sizeof(estados[0]);

	while (1)
	{
		cambiar(estados[num]);

		num += dir;

		if (num == max - 1 || num == 0)
		{
			dir = -dir; // cambia direccion
		}

		esperar();
	}
}
