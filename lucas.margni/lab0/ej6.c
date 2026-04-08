/* ¿Cuál es el valor en base 2 (binario) de i, j, k, m, n, p ? */

#include <stdio.h>

void print_binario_c(char var) {
    int tam = sizeof(char) * 8;

    for (int i = tam-1; i >= 0; i--) {
        printf("%d", (var >> i) & 1);
    }
    
}

void print_binario_uc(unsigned char var) {
    int tam = sizeof(unsigned char) * 8;

    for (int i = tam-1; i >= 0; i--) {
        printf("%d", (var >> i) & 1);
    }
    
}

int main() {
    char i = 'a';           // valor binario: 01100001 (igual que m)
    char j = 77;            // valor binario: 01001101 (igual que k y n)
    char k = 0x4D;          // valor binario: 01001101 (igual que j y n)
    unsigned char m = 'a';  // valor binario: 01100001 (igual que i)
    unsigned char n = 0x4d; // valor binario: 01001101 (igual que j y k)
    unsigned char p = 'A';  // valor binario: 01000001

    printf("Valor binario de i: ");
    print_binario_c(i);
    printf("\nValor binario de j: ");
    print_binario_c(j);
    printf("\nValor binario de k: ");
    print_binario_c(k);
    printf("\nValor binario de m: ");
    print_binario_uc(m);
    printf("\nValor binario de n: ");
    print_binario_uc(n);
    printf("\nValor binario de p: ");
    print_binario_uc(p);
    printf("\n");

    return 0;
}