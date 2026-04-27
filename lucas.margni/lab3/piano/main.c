/**********************************************************************
 *
 * main.c - piano para tocar notas musicales
 *
 **********************************************************************/

#include "serial.h"
#include "piano.h"

int main(void) {
    char carac = 0;

    /* Configurar el UART para el driver serial */
    serial_init();
    piano_init();

    while (1) {
        /* Esperamos recibir un caracter */
        carac = serial_get_char();

        /* Obtenemos la nota correspondiente */
        unsigned char nota = transformar_nota(carac);
        if(nota != -1) {
            reproducir_nota(nota);
        }

        /* Realizamos echo para testeo */
        serial_put_char(carac);
        serial_put_char(' ');
        serial_put_char(nota);
        serial_put_char('\n');
    }

    for (;;);

    return 0;
}

