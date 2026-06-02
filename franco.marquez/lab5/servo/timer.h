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
long long get_timer();
void actualizar_servo(uint16_t);

#endif /* _TIMER1_H */