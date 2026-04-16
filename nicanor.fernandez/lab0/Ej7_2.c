int main() {
    unsigned int array[5];
    array[2] = 99;

    unsigned int *pointer;
    pointer = &array[0];
    *(pointer+2) = 99;

    pointer = array;
}

/* Se crea un arreglo de 5 posiciones y se le asigna el valor 99 al arreglo en 2.
Luego se crea un puntero que se lo apunta a la primera posición del arreglo.
Luego se le asigna el valor 99 a donde apunta el puntero más 2 unsigned int, es decir, al arreglo en 2, lo que no cambia nada ya que esta posición ya tiene ese mismo valor.
Luego se iguala el puntero al arreglo, lo cual tampoco cambia nada porque el puntero estaba apuntando al inicio del arreglo desde un principio. */