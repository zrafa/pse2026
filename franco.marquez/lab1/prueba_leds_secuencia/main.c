
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
	volatile unsigned char estados[20];
	led_init();
	estados[0] = 0x00;
	estados[1] = 0x10;
	estados[2] = 0x00;
	estados[3] = 0x10;
	estados[4] = 0x18;
	estados[5] = 0x00;
	estados[6] = 0x10;
	estados[7] = 0x18;
	estados[8] = 0x1C;
	estados[9] = 0x00;
	estados[10] = 0x10;
	estados[11] = 0x18;
	estados[12] = 0x1C;
	estados[13] = 0x1E;
	estados[14] = 0x00;
	estados[15] = 0x10;
	estados[16] = 0x18;
	estados[17] = 0x1C;
	estados[18] = 0x1E;
	estados[19] = 0x1F;
	while (1) {
		for(volatile unsigned short i = 0; i < 20; i++)
		{
			pasarEstado(estados[i]); 
			esperar();
		}
		esperar();
		esperar();
		esperar();
		esperar();
    	}
}


