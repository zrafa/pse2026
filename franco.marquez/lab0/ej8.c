#include <stdio.h>

int main() {
    char a;
    a = (1 << 5);

    printf("Decimal : %d\n", a);
    printf("Hex     : 0x%X\n", a);
    return 0;
}
/*1 en binario (8 bits): 0 0 0 0 0 0 0 1
                                          << 5 (desplazar 5 posiciones a la izquierda)
 resultado            : 0 0 1 0 0 0 0 0
                        7 6 5 4 3 2 1 0   ← posición del bit
*/
