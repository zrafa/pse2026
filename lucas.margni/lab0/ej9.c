/*  En ocasiones queremos realizar un cómputo, cuyo resultado debe ser
    almacenado en un registro de 8 bits.

    ¿Qué sucede con el resultado de la siguiente operación? */

#include <stdio.h>

int main() {
    unsigned char res;
    unsigned char var;
    var = 190;
    res = (unsigned char)(var * 500) / 190;

    return 0;
}

/* En estos casos, donde queremos realizar una multiplicacion que da un numero bastante grande,
una variable unsigned char no va a ser capaz de almacenar tanto valor. Por lo tanto, al obtener el resultado
de la multiplicacion, se va a almacenar solamente los ultimos 8 bits del resultado. Luego, en la división, 
como es entre numero enteros nos va a dar el cociente de la division, que en este caso da 0. */