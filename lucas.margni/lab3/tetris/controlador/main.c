/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "pulsadores.h"

void main(void) {
    pulsadores_init();

    while(1) {
        verificar_pulsacion();
    }
}

