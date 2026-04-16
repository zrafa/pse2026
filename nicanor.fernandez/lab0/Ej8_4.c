#include <stdio.h>

int main() {
    unsigned char x = 11;

    printf("Bit 7 de x: %d\n", (x & 0b10000000) >> 7);
    printf("Bit 6 de x: %d\n", (x & 0b01000000) >> 6);
    printf("Bit 5 de x: %d\n", (x & 0b00100000) >> 5);
    printf("Bit 4 de x: %d\n", (x & 0b00010000) >> 4);
    printf("Bit 3 de x: %d\n", (x & 0b00001000) >> 3);
    printf("Bit 2 de x: %d\n", (x & 0b00000100) >> 2);
    printf("Bit 1 de x: %d\n", (x & 0b00000010) >> 1);
    printf("Bit 0 de x: %d\n", (x & 0b00000001) >> 0);

    return 0;
}