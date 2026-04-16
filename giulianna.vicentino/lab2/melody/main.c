#include "utils.h"
#include <stdint.h>

// frecuencias en hz DO, RE, MI, FA, SOL, LA, SI, DO alto
int escala[] = {262, 294, 330, 349, 392, 440, 494, 523};

int main(void) {
    parlante_init();

    while (1) {
        for (int i = 0; i < 8; i++) {
            
            tocar_nota(escala[i], 400);
            silencio(100);
        }

        silencio(2000); 
    }

    return 0;
}