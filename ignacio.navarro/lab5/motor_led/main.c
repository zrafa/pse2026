#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "serial.h"
#include "timer2_pwm.h"

int main(void) {
  adc_init();
  timer2_pwm_init();
  serial_init();

  while (1) {
    // leo potenciometro
    uint16_t val_adc = adc_get(0);

    // 1024 / 4 = 256
    uint8_t pwm_val = val_adc / 4;

    // valor para motor y para led
    timer2_set_pwm(pwm_val, pwm_val);

    _delay_ms(10);
  }
}