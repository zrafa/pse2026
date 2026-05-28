#include <stdint.h>
#include <util/delay.h>
#include "adc.h"
#include "serial.h"
#include <avr/io.h>

#define DO_US  956  // Do 5  (523 Hz) - Grave 
#define RE_US  758  // Mi 5  (659 Hz)
#define MI_US  637  // Sol 5 (784 Hz)
#define FA_US  478  // Do 6  (1046 Hz) - Medio
#define SOL_US 379  // Mi 6  (1318 Hz)
#define LA_US  318  // Sol 6 (1568 Hz)
#define SI_US  238  // Do 7  (2093 Hz) - Agudo 


uint16_t adc_puntos[]  = {0, 15, 40, 100, 250, 500, 800, 1023}; 

uint16_t freq_puntos[] = {200, 300, 400, 500, 600, 700, 800, 900}; 

uint16_t log_a_lineal(uint16_t adc_val) {
  // Si estamos en los extremos, devolvemos el mínimo o máximo directo
  if (adc_val <= adc_puntos[0]) return freq_puntos[0];
  if (adc_val >= adc_puntos[7]) return freq_puntos[7];

 
  for (int i = 0; i < 7; i++) {
    if (adc_val >= adc_puntos[i] && adc_val <= adc_puntos[i+1]) {
            
      
      uint32_t x = adc_val - adc_puntos[i];
      uint32_t delta_y = freq_puntos[i+1] - freq_puntos[i];
      uint32_t delta_x = adc_puntos[i+1] - adc_puntos[i];
            
       return freq_puntos[i] + ((x * delta_y) / delta_x);
    }
  }
  return 200; 
}

uint16_t escala_musical[] = {DO_US, RE_US, MI_US, FA_US, SOL_US, LA_US, SI_US};

int main(void) {
  adc_init();
    
  // Configura el Pin D8 (PB0) como salida para el parlante
  DDRB |= (1 << 0);

  uint16_t retardo_us = 1000; 
  uint16_t contador_ciclos = 50;

  while(1) {
    if (contador_ciclos >= 50) {
      uint16_t pot_val = adc_get(0);
            
       uint16_t freq = log_a_lineal(pot_val);
            
      uint32_t medio_periodo_us = 500000 / freq;
            
      if (medio_periodo_us > 80) {
	retardo_us = medio_periodo_us - 80;
      } else {
	retardo_us = 1; 
      }
            
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
