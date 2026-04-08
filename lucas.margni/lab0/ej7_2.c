/* Comprender el siguiente código. */

int main() {
    unsigned int array[5];  // se crea un arreglo de 5 posiciones
    array[2] = 99;          // en la 3er posicion se le asigna el valor 99

    unsigned int *pointer;  // se crea un puntero del mismo tipo que el arreglo
    pointer = &array[0];    // el puntero apunta a la primer posicion del arreglo
    *(pointer+2) = 99;      // en la posicion que apunta el puntero mas dos se le asigna 99
                            // es decir, en el arreglo en la posicion 2

    pointer = array;        // el valor del puntero se le asigna el valor del puntero que da inicio al arreglo
                            // en este caso es el mismo, ya que el puntero y el arreglo ambos apuntan a la pos 0

    return 0;
}