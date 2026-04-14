
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
	 int ms_espera = 25; // Con un ms de espera, no se llega a ver una imagen
	led_init();

unsigned char estados[16]; //Esto seria una imagen de una carita feliz
	estados[0] = 0x30;
	estados[1] = 0x00;
	estados[2] = 0x20;
	estados[3] = 0x40;
	estados[4] = 0x40;
	estados[5] = 0x30;
	estados[6] = 0x58;
	estados[7] = 0x18;
	estados[8] = 0x58;
	estados[9] = 0x0c;
	estados[10] = 0x40;
	estados[11] = 0x0c;
	estados[12] = 0x03;
	estados[13] = 0x8c;
	estados[14] = 0x0e;
	estados[15] = 0x8c;
	
	while (1) {
		for(short i = 0; i <= 7; i++)
		{
			pasarEstado(estados[i*2],estados[i*2+1]);
			esperar(ms_espera);
		}
		for(short j = 7; j >= 0; j--)
		{
			pasarEstado(estados[j*2],estados[j*2+1]);
			esperar(ms_espera);
		}
    	}
}


