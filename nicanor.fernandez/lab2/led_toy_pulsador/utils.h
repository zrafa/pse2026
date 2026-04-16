
/* utils.h - funciones de soporte al programa principal */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H

void delayms(int);
void led_init();
void siguiente_animacion();
void verificar_cambio_imagen();


#endif	/* _UTILS_H */
