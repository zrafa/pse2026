#include <stdio.h>

int main(){
	char var;
	var = (1 << 5);
	printf("var: %d \n", var);
}

/* La operación shift desplaza los valores de cada bit de una variable hacia la izquierda o derecha. En este caso a var se le asigna un 1 desplazado 6 bits hacia la derecha. 
El valor en base 2 de var es 0B00100000.
El valor en decimal de var es 32. */
