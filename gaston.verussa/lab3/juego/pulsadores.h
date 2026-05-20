
/* utils.h - funciones de soporte al programa principal */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _PULSADORES_H
#define _PULSADORES_H


void esperar();
void pulsadores_init();
int leer_pulsador(int num_pulsador);

#endif	/* _UTILS_H */
