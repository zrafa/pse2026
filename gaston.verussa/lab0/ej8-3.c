#define BIT3 3

#include <stdio.h>

int main(void)
{
	unsigned char status;

	printf("Los siguientes valores de status estan todos en hexagesimal \n");
	status = 0b00110101;
	printf("status vale %x \n",status);
	status = status | 0xFA;
	printf("Luego de status | 0xFA, status vale %x \n",status);
	status = status & 20;
	printf("Luego de status & 0xFA, status vale %x \n",status);
	status |= (1 << 6);
	printf("Luego de status | (1 << 6), status vale %x \n",status);
	status &= ~(1 << BIT3);
	printf("Luego de status & ~(1 << BIT3), status vale %x \n",status);
	status |= (1 << BIT3);
	printf("Luego de status | (1 << BIT3), status vale %x \n",status);
;
	return 0;
}
