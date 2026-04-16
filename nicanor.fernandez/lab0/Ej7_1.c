#include <stdio.h>

int main () {

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
	printf ("a=%i, lo apuntado por b=%i, el contenido de b=%X, y la direccion de b=%X \n", a, *b, b, &b);
	
	*b = 21;
}

/* Si al comenzar el programa el sistema asignó la dirección 0xFFA00004 al
arreglo x[] entonces el valor final del contenido de *ptr es 0xFFA0000C ya que se le suma 1 int 2 veces, lo que hace que termine desplazado 8 bytes terminando en la dirección de memoria de x[2] 
    
El valor final del contenido de la variable a es 21 ya que el puntero b apunta a la dirección de memoria de a, lo que hace que en la última línea del programa cambie su valor de 5 a 21.

La dirección de la variable x[2] es 0xFFA0000C, que es en la que finaliza el puntero *ptr.
*/