#include <stdio.h>

int main(){
	char var;
	var = ~(1 << 5);
	printf("var: %d \n", var);
}

/* La operación shift negada realiza el mismo procedimiento que la operación shift con la única diferencia que luego convierte todos los bits que tenían el valor 0 a 1 y viceversa, producto de la negación.
El valor en base 2 de var es 0B11011111.
El valor en decimal de 2 es -65.
*/