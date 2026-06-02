/* timer0.h
 * 
 * API para la aplicacion embebida 
 * META: ocultar el hardware a la aplicacion 
 *
 */

#include <stdint.h>

#define MODE_CTC 0
#define MODE_PWM 1

#define COUNTER_A 0
#define COUNTER_B 1

#define PRESCALER_1         0
#define PRESCALER_8         1
#define PRESCALER_64        2
#define PRESCALER_256       3
#define PRESCALER_1024      4
#define EXTERNAL_FALLING    5
#define EXTERNAL_RISING     6

#ifndef _TIMER0_H
#define _TIMER0_H

int8_t timer0_init(uint8_t, uint8_t, uint8_t);
int8_t timer0_set_counter(uint8_t, uint8_t);
uint8_t timer0_get_value();
void timer0_write_value(uint8_t);
int8_t timer0_enable_interrupts(uint8_t);
int8_t timer0_disable_interrupts(uint8_t);

#endif /* _TIMER0_H */