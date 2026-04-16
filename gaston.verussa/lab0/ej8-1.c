#include <stdio.h>

int main(void)
{
	char x = 1<<5;
	//	A falta de formato para imprimir en base 2, se hace manual
	printf("Su valor en binario es 00100000 \n");
	//	Imprime el valor en decimal, el cual es 32
	printf("Su valor en decimal es %d \n",x);
	return 0;
}
