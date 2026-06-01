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
void timer1_set_audio_sample(uint8_t dato_raw);

#endif /* _TIMER1_H */
