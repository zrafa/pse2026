#include <stdio.h>

int main(){
	unsigned char x = 11;
    x &= ~(3 << 0);
    printf("x: %d \n", x);
}