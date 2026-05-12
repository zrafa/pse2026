#include "serial.h"
#include <avr/io.h>
#include <util/delay.h>
#include "piano.h"

int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    speaker_init();
    
    while (rcvChar != 'q')
    {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();

        switch(rcvChar){
            case 'z': tocar_nota(0);
                break;
            case 'x': tocar_nota(1);
                break;
            case 'c': tocar_nota(2);
                break;
            case 'v': tocar_nota(3);
                break;
            case 'b': tocar_nota(4);
                break;
            case 'n': tocar_nota(5);
                break;
            case 'm': tocar_nota(6);
                break;
            default: silencio();
                break;
        }

    }

    for (;;);

    return 0;
}