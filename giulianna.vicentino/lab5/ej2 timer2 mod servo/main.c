#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "serial.h" 
#include "timer2.h" 
#include "adc.h"    
#include "servo.h"  
void serial_print_str(const char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    serial_put_char(str[i]);
  }
}



int main(void) {
  serial_init();
  timer2_init_ctc(); 
  adc_init();
  servo_init();
    
  sei(); 

  char buffer[16];
  uint32_t ticks_seguros;

  while (1) {
    cli();
    ticks_seguros = ticks_centesimas;
    sei();

    
    uint8_t centesimas = ticks_seguros % 100;
    uint8_t segundos   = (ticks_seguros / 100) % 60;
    uint8_t minutos    = (ticks_seguros / 6000);

      
    sprintf(buffer, "%02u:%02u:%02u\n", minutos, segundos, centesimas);
    serial_print_str(buffer);

        uint16_t valor_adc = adc_get(0);

     uint32_t ticks_pwm = 2000 + ((uint32_t)valor_adc * 2000) / 1023; //linealizacion

     servo_set_ticks((uint16_t)ticks_pwm);


	
    _delay_ms(20); 
  }

  return 0;
}
