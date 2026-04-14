/* Se desea ejecutar un bloque de código en C si el bit 3 de la variable
    x anterior está en 1. Complete la siguiente sentencia condicional if */

#include <stdio.h>

int main() {
    unsigned char x = 11;

    if((x & 0b00001000) >> 3 == 1) {
        printf ("el bit3 de la variable registro es 1 \n");
    }

    return 0;
}