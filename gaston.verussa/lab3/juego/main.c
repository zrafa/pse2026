/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "pulsadores.h"

unsigned char botones[3][2] =
{{'a', 'A'}, {'d', 'D'}, {'j', 'J'}};

int main(void)
{
    char rcvChar = 0;
    int i;
    /* Configure the UART for the serial driver */
    serial_init();
    pulsadores_init();
    unsigned char ultimo_valor[3];
    ultimo_valor[0] = 0;
    ultimo_valor[1] = 0;
    ultimo_valor[2] = 0;
    unsigned char valor_actual[3];
    valor_actual[0] = 0;
    valor_actual[2] = 0;
    valor_actual[2] = 0;

/*
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');

    serial_put_char('\r');
    serial_put_char('\n');
*/
    while (1)
    {
	esperar();
	for(i = 0; i < 3; i++)
	{
		valor_actual[i] = leer_pulsador(i);
		if(ultimo_valor[i] == 0 && valor_actual[i] == 1)
		{
			serial_put_char(botones[i][1]);
			serial_put_char('\r');
		}
		if(ultimo_valor[i] == 1 && valor_actual[i] == 0)
		{
			serial_put_char(botones[i][0]);
			serial_put_char('\r');
		}
		ultimo_valor[i] = valor_actual[i];
	}
    }

    return 0;
}

