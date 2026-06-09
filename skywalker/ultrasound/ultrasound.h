
/* CONSTANTES DE DIRECCIONES */
#define PUERTO_D 0x2B  
#define DDR_D 0x2A
#define PIN_D 0x29
#define PUERTO_C 0x28  
#define DDR_C 0x27
#define PIN_C 0x26
#define PUERTO_B 0x25  
#define DDR_B 0x24
#define PIN_B 0x23


#ifndef _ULTRASOUND_H
#define _ULTRASOUND_H

void ultrasound_init(char, char);
int ultrasound_get();

#endif 
