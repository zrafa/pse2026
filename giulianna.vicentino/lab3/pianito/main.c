/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/
#include "serial.h"
#include <avr/io.h>
#include <util/delay.h>

#define DO_US  956  // Do 5  (523 Hz) - Grave 
#define RE_US  758  // Mi 5  (659 Hz)
#define MI_US  637  // Sol 5 (784 Hz)
#define FA_US  478  // Do 6  (1046 Hz) - Medio
#define SOL_US 379  // Mi 6  (1318 Hz)
#define LA_US  318  // Sol 6 (1568 Hz)
#define SI_US  238  // Do 7  (2093 Hz) - Agudo 

void tocar_nota(uint16_t retardo_us) {
  uint16_t ciclos = 80000 / retardo_us;

  for (uint16_t i = 0; i < ciclos; i++) {
    PORTB |= (1 << 0);  /* Pone el Pin D8 en ALTO */
    for (uint16_t d = 0; d < retardo_us; d++) _delay_us(1);
    PORTB &= ~(1 << 0); /* Pone el Pin D8 en BAJO */
    for (uint16_t d = 0; d < retardo_us; d++) _delay_us(1);
  }
}

int main(void)
{
  char tecla = 0;

  /* Configure the UART for the serial driver */
  serial_init();
  
  /* Configuracion del pin del speaker (PB0 / Pin D8) como salida */
  DDRB |= (1 << 0);

  while (tecla != 'q')
    {//espera activa de una letra
      tecla = serial_get_char();

      switch(tecla) {
      case 'a': tocar_nota(DO_US); break;
      case 's': tocar_nota(RE_US); break;
      case 'd': tocar_nota(MI_US); break;
      case 'f': tocar_nota(FA_US); break;
      case 'g': tocar_nota(SOL_US); break;
      case 'h': tocar_nota(LA_US); break;
      case 'j': tocar_nota(SI_US); break;
      default:  break; /* Si toca otra tecla, no hace nada */
      }
    }
 
  for (;;);

  return 0;
}
