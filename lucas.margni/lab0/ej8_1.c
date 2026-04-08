/* Comprender una operación shift. Por ejemplo: (1 << 5).
    Escriba un programa que defina una variable de tipo char.
    Asigne la operacion shift mencionada arriba a esa variable.
    Indique cual es el valor en base 2 de la variable de tipo char.
    Indique cual es el valor en decimal. */

#include <stdio.h>

int main() {
    char var = 3;
    char res = var <<  1;

    printf("Valor de var: %d\n", var); // 3 en binario es 00000011
    printf("Valor de res: %d\n", res); // 6 en binario es 00000110
    // efectivamente, se movieron los bits de var 1 posicion a la izquierda

    return 0;
}

/* La operacion shift en c manipula los bits de una variable.
Lo que hace es mover una catidad especifica de bits hacia la derecha o izquierda
una cantidad determinada de veces, rellenando el otro espacio de 0s
Se escribe de la forma a >> b o a << b.
Donde el resultado sera el valor de a moviendo los bits b veces hacia la derecha (izquierda)
eliminando lo valores que estan más hacia la derecha (izquierda) en cada paso y rellenando
los valores nuevos de la izuquierda (derecha) que van apareciendo */