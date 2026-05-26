/**********************************************************************
 *
 * Filename: timer.h
 * 
 * API para la aplicacion embebida 
 * META: ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#include <stdint.h>

#ifndef _TIMER1_H
#define _TIMER1_H

void init_timer();
void actualizar_tope(uint16_t)
ISR(TIMER1_COMPA_vect)

#endif /* _TIMER1_H */