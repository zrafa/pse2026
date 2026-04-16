#define BIT3 3

int main(){
    unsigned char status;   

    status = 0b00110101;
    status = status | 0xFA; //0xFA en binario es 0b11111010, el resultado de la operación | es 0b11111111
    status = status & 20; //20 en binario es 0b00010100, el resultado de la operación & es 0b00010100
    status |= (1 << 6); //1 << 6 en binario da el valor 0b00100000, el resultado de la operación | es 0b01010100
    status &= ~(1 << BIT3) //~(1 << BIT3) en binario da el valor 0b11110111, el resultado de la operación & es 0b01010100
    status |= (1 << BIT3) //1 << BIT3 en binario da el valor 0b00001000, el resultado de la operación | es 0b01011100

}

/* El operador & realiza una operación AND lógica, devolviendo 1 si ambos bits comparados tienen el valor 1 y 0 en cualquier caso distinto.
El operador | realiza una operación OR lógica, devolviendo 0 si ambos bits comparados tienen el valor 0 y 1 si alguno de ellos o ambos tienen el valor 1.
Estas operaciones nos permiten conservar o eliminar bits específicos de las variables.*/