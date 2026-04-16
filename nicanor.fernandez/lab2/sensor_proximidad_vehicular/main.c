#include "utils.h"

int main(void) {	
	vehiculo_init();

	while(1) {
		int dist = ultrasound_get_distance();
		
		if(dist < 30) {
			reproducir_pitido();
			silencio(dist * 1000);
		}
	}
}
