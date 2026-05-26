#include <avr/io.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>

#include "adc.h"
#include "serial.h"
#include "timer1.h"

// esta funcion es util para mandar multiples datos dentro de la misma linea,
// separados por - (segun dato) y \n para nueva linea
void enviar_datos_formateados(uint16_t pos, uint8_t boton) {
  char buffer[7];

  itoa(pos, buffer, 10);
  for (int i = 0; buffer[i] != '\0'; i++) {
    serial_put_char(buffer[i]);
  }

  serial_put_char(' ');

  itoa(boton, buffer, 10);
  serial_put_char(buffer[0]);

  serial_put_char('\n');
}

uint16_t linealizar_potenciometro(uint16_t pos_raw) {
    float valor_norm = (float)pos_raw / 1023.0f;
    float valor_corregido = powf(valor_norm, 0.3f);  
    
    return (uint16_t)(valor_corregido * 1023.0f);
}

int main(void) {
  adc_init();
  timer1_init();
  serial_init();

  while (1) {
    // leer potenciometro
    uint16_t pot1 = adc_get(0);

    uint16_t pot = linealizar_potenciometro(pot1);

    servo_set_angle(pot);

    _delay_ms(20);
  }
}