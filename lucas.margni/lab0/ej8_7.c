/* Escriba una sentencia en C para poner asertar los bits7 y bit6 
    (ponerlos en uno), sin modificar el resto de los bits. */

#include <stdio.h>

int main() {
    unsigned char x = 11;
    unsigned char res;

    res = x | 0b11000000;

    printf("x: %i\n", x);
    printf("res: %i\n", res);

    return 0;
}