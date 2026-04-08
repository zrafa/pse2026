/* Comprender una operación shift que luego se niega. Por ejemplo: ~(1 << 5).
    Escriba un programa que defina una variable de tipo char.
    Asigne a la variable la operacion shift mencionada arriba.
    Indique cual es el valor en base 2 de la variable de tipo char.
    Indique cual es el valor en decimal. */

#include <stdio.h>

int main() {
    char var = 3;
    char res = ~(var <<  1);

    printf("Valor de var: %d\n", var); // 3 en binario es 00000011
    printf("Valor de res: %d\n", res); // -7 en binario es 11111001 (00000110 invertido)
    // efectivamente, se movieron los bits de var 1 posicion a la izquierda y se invirtio cada bit

    return 0;
}

/* El operador de complemeto de bits (~) sirve para invertir cada uno de los bits,
transformando cada 0 en 1, y cada 1 en 0 en todo el numero que se le pase */