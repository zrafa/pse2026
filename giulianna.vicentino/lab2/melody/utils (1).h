/* utils.h - funciones de soporte al programa principal para el parlante */

/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino.
 * Usaremos el pin 8 (PB0) para el parlante.
 */

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h> // Necesario para usar el tipo de dato uint16_t

// Inicializa el pin del parlante como salida
void parlante_init(void);

// Genera una onda cuadrada para producir una nota musical
void tocar_nota(uint16_t frecuencia, uint16_t duracion_ms);

// Genera una pausa exacta en milisegundos
void silencio(uint16_t duracion_ms);

#endif /* _UTILS_H */