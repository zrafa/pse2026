#include "utils.h"

#define DO 0
#define RE 1
#define MI 2
#define FA 3
#define SOL 4
#define LA 5
#define SI 6
#define SILENCIO -1

char cancion[] = {
	DO, DO, SOL, SOL, LA, LA, SOL, SILENCIO,
	FA, FA, MI, MI, RE, RE, DO, SILENCIO,
	SOL, SOL, FA, FA, MI, MI, RE, SILENCIO,
	SOL, SOL, FA, FA, MI, MI, RE, SILENCIO,
	DO, DO, SOL, SOL, LA, LA, SOL, SILENCIO,
	FA, FA, MI, MI, RE, RE, DO
};

int main(void) {	
	melody_init();

	volatile int tam = sizeof(cancion) / sizeof(cancion[0]);
	volatile unsigned int i;

	for(i = 0; i < tam; i++) {
		if(cancion[i] == SILENCIO) {
			silencio();
		} else {
			reproducir_nota(cancion[i]);
		}
	}
}
