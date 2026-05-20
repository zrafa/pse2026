/**********************************************************************
 *
 * Filename: timer1.h
 * 
 * API para la aplicacion embebida 
 * META: ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h>

#ifndef _TIMER1_H
#define _TIMER1_H

void timer1_init();
void timer1_set_comparador(uint16_t);

#endif /* _TIMER1_H */