/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "sound.h"

volatile unsigned char * ddr_b = (unsigned char *) 0x24;

int main(void)
{
    char tecla = 0;

    serial_init();
    *ddr_b |= (1 << 5); // Configurar PB5 como salida para el parlante

    serial_put_char('p');
    serial_put_char('i');
    serial_put_char('a');
    serial_put_char('n');
    serial_put_char('o');
    serial_put_char('\r');
    serial_put_char('\n');

    while (tecla != 'q') 
    {
        tecla = serial_get_char();

        if (tecla == 'a') sound(262, 300);      // DO
        else if (tecla == 's') sound(294, 300); // RE
        else if (tecla == 'd') sound(330, 300); // MI
        else if (tecla == 'f') sound(349, 300); // FA
        else if (tecla == 'g') sound(392, 300); // SOL
        else if (tecla == 'h') sound(440, 300); // LA
        else if (tecla == 'j') sound(494, 300); // SI
        else if (tecla == 'k') sound(523, 300); // DO5
    }

    for (;;);

    return 0;
}