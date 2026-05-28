#ifndef TIMER2_H_
#define TIMER2_H_

#include <stdint.h>

// Variable global que cuenta las centésimas (declarada como externa para poder leerla en el main)
extern volatile uint32_t ticks_centesimas;

// Función para inicializar el timer2 en modo CTC a 100Hz
void timer2_init_ctc(void);

#endif /* TIMER2_H_ */
