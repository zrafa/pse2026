#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

// Inicializa el hardware del Timer 1 para controlar el servo
void servo_init(void);

// Permite cambiar el ángulo del servo pasándole los ticks (entre 2000 y 4000)
void servo_set_ticks(uint16_t ticks);

#endif /* SERVO_H_ */
