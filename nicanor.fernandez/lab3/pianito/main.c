/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "melody.h"


int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    /*Inicializo el speaker*/
    melody_init();
    
    while (rcvChar != 'q')
    {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();

        switch(rcvChar){
            case 'a': reproducir_nota(0);
                break;
            case 's': reproducir_nota(1);
                break;
            case 'd': reproducir_nota(2);
                break;
            case 'f': reproducir_nota(3);
                break;
            case 'g': reproducir_nota(4);
                break;
            case 'h': reproducir_nota(5);
                break;
            case 'j': reproducir_nota(6);
                break;
            default: silencio();
                break;
        }

        /* Echo the character back along with a carriage return and line feed */
        /* serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n'); */
    }

    for (;;);

    return 0;
}

