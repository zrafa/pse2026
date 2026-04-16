#include <stdio.h>

int main(){
	unsigned char x = 11;
    x |= (3 << 6);
    printf("x: %d \n", x);
}