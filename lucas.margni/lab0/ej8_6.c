/* Escriba una sentencia en C para eliminar los bits2, bit1 y bit0
    (ponerlos en cero), sin modificar el resto de los bits. */

#include <stdio.h>

int main() {
    unsigned char x = 11;
    unsigned char res;

    res = x & 0b11111000;

    printf("x: %i\n", x);
    printf("res: %i\n", res);

    return 0;
}