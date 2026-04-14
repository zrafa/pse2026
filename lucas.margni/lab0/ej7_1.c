/* Comprender las siguientes definiciones y operaciones. */

#include <stdio.h>

int main() {
    int x[3];
    int *ptr;
    char a;
    char *b;

    x[0] = 1024;
    x[1] = 32;
    x[2] = -1;
    ptr = &x[0];
    ptr++;
    ptr++;

    a = 5;
    b = &a;
    printf("a=%i, lo apuntado por b=%i, el contenido de b=%X, y la direccion de b=%X \n", a, *b, b, &b);

    *b = 21;

    return 0;
}

/* Si al comenzar el programa el sistema asignó la dirección 0xFFA00004 al arreglo x[], 
	¿Cuál es el valor final del contenido de ptr al finalizar la ejecución del programa?

    ptr apunta a la direccion de x[] en su primera posicion. Luego se le suma 1 dos veces.
    Como ptr se le dice que es un putero a enteros, cada vez que se le suma 1 se movera la cantidad de
    posiciones como ocupa un arreglo (cada vez 4 bytes). Como inicia en la direccion 0xFFA00004, al sumarle 2
    terminara en la posicion 0xFFA0000C (8 bytes mas a la derecha).

	¿Cuál es el valor final del contenido de la variable 'a' al finalizar el programa?

    Como la variable b es un puntero a la variable a, y luego se realiza la linea '*b = 21' (que significa
    que modifiques el valor de la posicion de memoria que apunta b, que en este caso es a), a termina con
    el valor 21.

	¿Cuál es la dirección de la variable x[2]?
    
    La direccion de esta variable es al que termina ptr al finalizar el programa, es decir 0xFFA0000C */