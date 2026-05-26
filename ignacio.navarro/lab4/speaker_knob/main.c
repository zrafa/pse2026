#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "adc.h"
#include "serial.h"

#define DO_US 956   // Do 5  (523 Hz) - Grave
#define RE_US 758   // Mi 5  (659 Hz)
#define MI_US 637   // Sol 5 (784 Hz)
#define FA_US 478   // Do 6  (1046 Hz) - Medio
#define SOL_US 379  // Mi 6  (1318 Hz)
#define LA_US 318   // Sol 6 (1568 Hz)
#define SI_US 238   // Do 7  (2093 Hz) - Agudo

// puntos de cambio
uint16_t adc_puntos[] = {0, 15, 40, 100, 250, 500, 800, 1023};
// frecuencias lineales
uint16_t freq_puntos[] = {200, 300, 400, 500, 600, 700, 800, 900};

uint16_t log_a_lineal(uint16_t adc_val) {
  // si se excede se retorna el max o min
  if (adc_val <= adc_puntos[0]) return freq_puntos[0];
  if (adc_val >= adc_puntos[7]) return freq_puntos[7];

  // observar en que frecuencia cayo adc_val
  for (int i = 0; i < 7; i++) {
    if (adc_val >= adc_puntos[i] && adc_val <= adc_puntos[i + 1]) {
      // interpolacion lineal
      uint32_t x = adc_val - adc_puntos[i];
      uint32_t delta_y = freq_puntos[i + 1] - freq_puntos[i];
      uint32_t delta_x = adc_puntos[i + 1] - adc_puntos[i];

      return freq_puntos[i] + ((x * delta_y) / delta_x);
    }
  }
  return 200;  // por si acaso
}

uint16_t escala_musical[] = {DO_US, RE_US, MI_US, FA_US, SOL_US, LA_US, SI_US};

int main(void) {
  adc_init();

  // pin D8 (PB0) como salida para el parlante
  DDRB |= (1 << 0);
  uint16_t retardo_us = 1000;  // valor inicial
  uint16_t contador_ciclos = 50;

  while (1) {
    // cada 50 ciclos
    if (contador_ciclos >= 50) {
      uint16_t pot_val = adc_get(0);

      // freq linealizada
      uint16_t freq = log_a_lineal(pot_val);

      // frecuencia a microsegundos de retardo (medio periodo)
      retardo_us = 500000 / freq;

      contador_ciclos = 0;
    }

    PORTB |= (1 << 0);
    for (uint16_t d = 0; d < retardo_us; d++) _delay_us(1);

    PORTB &= ~(1 << 0);
    for (uint16_t d = 0; d < retardo_us; d++) _delay_us(1);

    contador_ciclos++;
  }

  return 0;
}
