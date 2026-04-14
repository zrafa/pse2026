
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
	const int ms_espera = 25;
	led_init();

	const unsigned char estados[16] = {
  		0x30, 0x00, 0x20, 0x40, 0x40, 0x30, 0x58, 0x18, 0x58, 0x0c, 0x40, 0x0c, 0x03, 0x8c, 0x0e, 0x8c
	};
	
	while (1) {
		for(short i = 0; i <= 15; i=i+2)
		{
			pasarEstado(estados[i],estados[i+1]); 
			esperar(ms_espera);
		}
		for(short j = 15; j >= 0; j=j-2)
		{
			pasarEstado(estados[j],estados[j+1]); 
			esperar(ms_espera);
		}
    	}
}


