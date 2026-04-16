#include <stdio.h>

int main() {
    unsigned char x = 11;

    if((x & 0b00001000) >> 3 == 1) {
        printf ("el bit3 de la variable registro es 1 \n");
    }

    return 0;
}