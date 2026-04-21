/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"

int main(void) {
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    serial_put_char('h');
    serial_put_char('e');
    serial_put_char('l');
    serial_put_char('l');
    serial_put_char('o');
    serial_put_char(' ');
    serial_put_char('m');
    serial_put_char('y');
    serial_put_char(' ');
    serial_put_char('f');
    serial_put_char('r');
    serial_put_char('i');
    serial_put_char('e');
    serial_put_char('n');
    serial_put_char('d');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q') {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();

        /* Echo the character back along with a carriage return and line feed */
        serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n');
    }

    for (;;);

    return 0;
}

