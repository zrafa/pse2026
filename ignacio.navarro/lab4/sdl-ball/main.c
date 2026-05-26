#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#include "adc.h"
#include "serial.h"

#include <stdlib.h>
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

int main(void) {
  adc_init();
  serial_init();

  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);

  while (1) {
    uint16_t pos = adc_get(0);             // leer datos del potenciometro
    uint8_t boton = !(PIND & (1 << PD2));  // boton: 1 pulsado 0 no pulsado

    enviar_datos_formateados(pos, boton);

    _delay_ms(20);
  }
}
