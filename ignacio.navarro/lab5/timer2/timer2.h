/**********************************************************************
 *
 * Filename:    timer2.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _TIMER2_H
#define _TIMER2_H

void timer2_init(void);
extern volatile uint32_t ticks_centis;

#endif /* _TIMER2_H */