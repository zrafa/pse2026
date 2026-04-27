
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
	volatile unsigned char estados[6];
	led_init();
	estados[0] = 0x30;
	estados[1] = 0x18;
	estados[2] = 0x2C;
	estados[3] = 0x06;
	estados[4] = 0x23;
	estados[5] = 0x01;

	while (1) {
		for(short i = 0; i <= 5; i++)
		{
			pasarEstado(estados[i]); 
			esperar();
		}
		for(short j = 5; j >= 0; j--)
		{
			pasarEstado(estados[j]); 
			esperar();
		}
    	}
}


