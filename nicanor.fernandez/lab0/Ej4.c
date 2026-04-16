#include <stdio.h>

int main() {
	char a = 'M';
   	printf ("a = %i \n", a);
   	printf ("La letra %c \n", a);
}

/* El valor numérico de a es de 77. El tipo de dato char almacena 1 byte que cuando se le asigna un caracter se almacena su valor ASCII, en el caso del caracter 'M' es de 77, por esto cuando se imprime como %i (que se utiliza para imprimir enteros) se imprime ese valor y cuando se imprime con %c (que se utiliza para imprimir caracteres) se imprime la letra M */
