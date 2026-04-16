#include <stdio.h>

int main(void)
{
	char x = 11;
	printf("x vale %d, su valor en binario es 00001011 \n", x);
	for(char i = 0; i < 7; i++)
	{
		printf("El valor del bit n° %d es %d \n",i,(x >> i) & (1 << 0));
	}
	return 0;
}
