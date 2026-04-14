/* Comprender los operadores AND y OR (& y |)
    Para poder verificar el estado de un bit.
    Para poder obtener sólo una parte de los bits. Por ejemplo: & 0xF0 */

#include <stdio.h>

#define BIT3 3

int main() {
    unsigned char status;

    status = 0b00110101;
    status = status | 0xFA; // 0xFA = 0b11111010
                            // 0b00110101 or 0b11111010 = 0b11111111
    status = status & 20;   // 20 = 0b00010100
                            // 0b11111111 and 0b00010100 = 0b00010100
    status |= (1 << 6);     // 1 << 6 = 0b000000001 << 6 = 0b01000000
                            // 0b00010100 or 0b01000000 = 0b01010100
    status &= ~(1 << BIT3); // ~(1 << BIT3) = ~(0b00000001 << 3) = ~(0b00001000) = 0b11110111
                            // 0b01010100 and 0b11110111 = 0b01010100
    status |= (1 << BIT3);  // 1 << BIT3 = 0b00000001 << 3 = 0b00001000
                            // 0b01010100 or 0b00001000 = 0b01011100
    
    printf("Valor final de status: %d\n", status); // valor final 92 (0b01011100)

    return 0;
}

/* El operador and (&) realiza operaciones bit a bit entre dos valores, retornando
1 si ambos bits que se comparan son 1, y en otro caso devuelve 0.
El operador or (|) realiza operaciones bit a bit entre dos valores, retornando
0 si ambos bits que se comparan son 0, y en otro caso devuelve 1.

Si queremos verificar el valor de un solo bit en una variable, debemos realizar la operacion and
para 'borrar' el resto de bits de dicha variable, y luego realizar un shift para que el bit
quede a la derecha de todo. Por ejemplo, si queremos ver el 4 bit (de derecha a izquierda) de una
variable var, tendremos que realizar (var & 0b000010000) >> 4

Si queremos obtener solo una parte de los bits de una variable, debemos realizar la misma operacion
que antes, pero poner mas cantidad de 1s en el and que se haga con dicha variable, indicando asi los bits
que queremos mantener */