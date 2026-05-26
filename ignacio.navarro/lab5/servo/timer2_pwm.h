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

void timer2_pwm_init(void);
void timer2_set_pwm(uint8_t, uint8_t);

#endif /* _TIMER2_H */