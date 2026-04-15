#include "utils.h"

#define N_IMAGENES    3
#define N_COLUMNAS    8
#define MS_ESPERA     25 //cambiar a 1 para ver el efecto bien

unsigned char imagenes[N_IMAGENES][N_COLUMNAS][2] = {
    {   /* imagen 0: pokebola */
        {0b00011000, 0b00011000},
        {0b01111110, 0b01111110},
        {0b11111111, 0b11111111},
        {0b11111111, 0b11111111},
        {0b11111111, 0b11111111},
        {0b11111111, 0b11111111},
        {0b01111110, 0b01111110},
        {0b00011000, 0b00011000}
    },
    {   /* imagen 1: carita feliz */
        {0b00000000, 0b00000000},
        {0b00000000, 0b01100110},
        {0b11000011, 0b01100110},
        {0b11000011, 0b00000000},
        {0b11000011, 0b00000000},
        {0b01100110, 0b00000000},
        {0b00111100, 0b00000000},
        {0b00000000, 0b00000000}
    },
    {   /* imagen 2: corazon */
        {0b00000000, 0b00000000},
        {0b01100110, 0b01100110},
        {0b11111111, 0b11111111},
        {0b11111111, 0b11111111},
        {0b01111110, 0b01111110},
        {0b00111100, 0b00111100},
        {0b00011000, 0b00011000},
        {0b00000000, 0b00000000}
    }
};


int imagen_actual = 0;
int pulsador_antes = 0;
int pulsador_ahora = 0;

int main(void) {
    short i;
   
    led_init();
    pulsador_init();   /* configurar pin del pulsador como entrada */

    while (1) {

        /* --- mostrar imagen actual (un barrido de ida) --- */
        for (i = 0; i < N_COLUMNAS; i++) {
            pasarEstado(
                imagenes[imagen_actual][i][0],
                imagenes[imagen_actual][i][1]
            );
            esperar(MS_ESPERA);

            /* leer pulsador dentro del loop para no perder pulsaciones */
            pulsador_ahora = leer_pulsador();
            if (pulsador_ahora && !pulsador_antes) {
                /* flanco ascendente: recién se presionó */
                imagen_actual++;
                if (imagen_actual >= N_IMAGENES)
                    imagen_actual = 0;   /* volver a la primera */
            }
            pulsador_antes = pulsador_ahora;
        }
    }
}