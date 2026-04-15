#include <stdio.h>

int main() {
    char b;
    b = ~(1 << 5);

    printf("Decimal : %d\n", b);
    printf("Hex     : 0x%X\n", (unsigned char)b);
    return 0;
}
/*(1 << 5)   : 0 0 1 0 0 0 0 0
 ~(1 << 5)  : 1 1 0 1 1 1 1 1   ← se invierten TODOS los bits
              7 6 5 4 3 2 1 0 */