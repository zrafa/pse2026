/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "speaker.h"
#include "led.h"

#define TIEMPO 500

int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();
    piezo_init();
    led_init();

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();

	serial_put_char('|');
	volatile unsigned char flag = 0;
	switch(rcvChar){
		case 'a':
			tocar_nota(0,TIEMPO);
			break;
		case 's':
			tocar_nota(1,TIEMPO);
			break;
		case 'd':
			tocar_nota(2,TIEMPO);
			break;
		case 'f':
			tocar_nota(3,TIEMPO);
			break;
		case 'g':
			tocar_nota(4,TIEMPO);
			break;
		case 'h':
			tocar_nota(5,TIEMPO);
			break;
		case 'j':
			tocar_nota(6,TIEMPO);
			break;
		case 'k':
			tocar_nota(7,TIEMPO);
			break;
		case 'e':
			led_on();
			break;
		case 'p':
			led_off();
			break;
		default:
			flag=1;
	}
	if(flag > 0)
	{
        	serial_put_char(rcvChar);
        	serial_put_char('\r');
        	serial_put_char('\n');
		silencio(200);
	}

	serial_put_char('|');
    }

    for (;;);

    return 0;
}

