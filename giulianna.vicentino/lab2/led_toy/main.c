#include "utils.h"

unsigned int flecha[8] = {
    0x000, 0x010, 0x030, 0xFFF, 0xFFF, 0x030, 0x010, 0x000};

unsigned int corazon_centrado[8] = {
    0x000,
    0x01C << 3,
    0x03E << 3,
    0x07E << 3,
    0x07E << 3,
    0x03E << 3,
    0x01C << 3,
    0x000};

// Una imagen de 8 columnas donde todos los LEDs están apagados
unsigned int vacio[8] = {
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
};

unsigned int reloj_arena[10] = {
    0xFFF, // Base (12 LEDs prendidos)
    0x7EE, // Se va cerrando
    0x3DC,
    0x1B8,
    0x0F0,
    0x0F0, // Centro
    0x1B8,
    0x3DC,
    0x7EE,
    0xFFF  // Techo
};

// Carita feliz (Smiley face) - 12 bits (usando bits centrales para 12 LEDs)
// Cada columna es un unsigned int (16 bits, usamos los 12 bajos)
unsigned int carita_feliz[8] = {
    0x3C0, // 0011 1100 0000 (Lado izquierdo, borde)
    0x420, // 0100 0010 0000 (Contorno)
    0x910, // 1001 0001 0000 (Contorno, ojo izquierdo y borde boca)
    0xA10, // 1010 0001 0000 (Ojo derecho y contorno)
    0xA10, // 1010 0001 0000 (Mismo contorno para el medio de los ojos)
    0x910, // 1001 0001 0000 (Ojo izquierdo y borde boca)
    0x420, // 0100 0010 0000 (Contorno)
    0x3C0  // 0011 1100 0000 (Lado derecho, borde)
};

// Imagen: Rombo geométrico que usa los 12 LEDs (D2-D13)
// El bit 0 es D2, el bit 11 es D13. Hexadecimal F = 1111 (4 unos).
unsigned int rombo_geometrico[8] = {
    0x030, // 0000 0011 0000 (Punta central de 12 bits)
    0x0F0, // 0000 1111 0000 (Se abre)
    0x3CF, // 0011 1100 1111 (Se abre más, con hueco central opcional)
    0xFFF, // 1111 1111 1111 (Centro total, 12 LEDs prendidos)
    0xFFF, // 1111 1111 1111 (Centro total duplicado para grosor)
    0x3CF, // 0011 1100 1111 (Se cierra)
    0x0F0, // 0000 1111 0000 (Se cierra)
    0x030  // 0000 0011 0000 (Punta central)
};

int main(void) {
    led_toy_init();
    input_init();

    int imagen_actual = 0;
    int estado_anterior = 0;

    while (1) {
        int presionado = boton_presionado();
        
        if (presionado && !estado_anterior) {
            imagen_actual++;
            if (imagen_actual > 2) imagen_actual = 0; 
        }
        estado_anterior = presionado;

        for (int i = 0; i < 8; i++) {
            unsigned int columna_a_mostrar;
            
            switch(imagen_actual) {
                case 0: columna_a_mostrar = carita_feliz[i]; break;
                case 1: columna_a_mostrar = rombo_geometrico[i]; break;
                case 2: default: columna_a_mostrar = vacio[i]; break;
            }

            display_column(columna_a_mostrar);
            delayms(1);
        }

        display_column(0);
        delayms(8);
    }
}