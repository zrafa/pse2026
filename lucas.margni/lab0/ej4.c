/* Explique la difercia en la salida de las siguientes instrucciones. */

#include <stdio.h>

int main() {
    char a = 'M';
    printf ("a = %i \n", a);
    printf ("La letra %c \n", a);

    /* char es un tipo de dato que almacena 1 byte. Este dato puede ser tanto un caracter como un entero de poco tamaño.
    Es por esta razon que en los distintos prints se mostraran diferentes salidas. 
    Por un lado, cuando se realiza %i muestra su valor como un entero (i de integer).
    Po otro lado, cuando se realiza %c muestra su valor como un caracter (c de character). */

    return 0;
}