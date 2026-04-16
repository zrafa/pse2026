#include "utils.h"
#include <stdint.h>

// Frecuencias en Hz: DO, RE, MI, FA, SOL, LA, SI, DO alto
uint16_t escala[] = {262, 294, 330, 349, 392, 440, 494, 523};

int main(void) {
  parlante_init(); //tiene que estar si o si!! sino no detecta al speaker

    while (1) {
        for (uint8_t i = 0; i < 8; i++) {
            
            tocar_nota(escala[i], 400); // Suena la nota por 400ms
            silencio(100);              //100ms entre notas
      

       
        silencio(2000); 
    }

    return 0;
}
