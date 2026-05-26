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
void timer1_setvalor(uint16_t);

#endif /* _TIMER1_H */