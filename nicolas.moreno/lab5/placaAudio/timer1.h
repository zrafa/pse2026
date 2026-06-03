/**********************************************************************
 *
 * Filename:    timer1.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _TIMER1_H
#define _TIMER1_H

void timer1_init(void);
extern volatile uint16_t muestra_actual;

#endif /* _TIMER1_H */