/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"


int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    /* Inicializo los puertos de los pulsadores */
    led_init();

    while(1){
        verificar_caracter();
    }

    for (;;);

    return 0;
}

