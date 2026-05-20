/**********************************************************************
 *
 * Filename: timer2.h
 * 
 * API para la aplicacion embebida 
 * META: ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h>

#ifndef _TIMER2_H
#define _TIMER2_H

void timer2_init();
uint16_t timer2_get_ticks();
void timer2_set_comparadores(uint8_t);

#endif /* _TIMER2_H */