/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "pulsadores.h"

unsigned char botones[2] =
{'a', 'd'};

int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();
    pulsadores_init();

    unsigned char ultimo_valor[2];
    unsigned char valor_actual[2];

    ultimo_valor[0] = 0;
    ultimo_valor[1] = 0;

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (1)
    {
	esperar();
	for(int i = 0; i < 2; i++)
	{
		valor_actual[i] = leer_pulsador(i+1);
		if(valor_actual[i] == 1 && ultimo_valor[i] == 0)
		{
			serial_put_char(botones[i]);
		}
		ultimo_valor[i] = valor_actual[i];
	}
    }

    return 0;
}

