#include <stdio.h>

int main(void)
{
	char x = ~(1<<5);
	//	A falta de formato para imprimir en base 2, se hace manual
	printf("Su valor en binario es 11011111 \n");
	//	Imprime el valor en decimal
	printf("Su valor en decimal es %d \n",x);
	return 0;
}
